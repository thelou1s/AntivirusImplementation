package com.avira.antivirusimplementation;

import android.content.Intent;
import android.support.v4.content.LocalBroadcastManager;
import android.util.Log;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

/**
 * @author ovidiu.buleandra
 *
 * singleton Antivirus object that is used to communicate with the native part through the JNI bridge
 *
 */
public class Antivirus {
    private static final String TAG = Antivirus.class.getSimpleName();

    // instance variable for the singleton
    private static Antivirus INSTANCE;
    // curent engine file format version
    private static final int MAVAPI_VERSION = 3;

    private static final int REPORT_FILE_STATUS = 0;

    public static final String ACTION_SCAN_FINISHED = "com.avira.antivirusimplementation.action.scan_finished";
    public static final String EXTRA_PATH = "extra_path";
    public static final String EXTRA_SCAN_RESULT = "extra_scan_result";

    private ExecutorService singleThreadExecutor;
    private long threadContextPointer = 0;

    /**
     * singleton instance retrieval
     * @return Antivirus instance
     */
    public synchronized static Antivirus getInstance() {
        if (INSTANCE == null) {
            INSTANCE = new Antivirus();
        }
        return INSTANCE;
    }

    /**
     * static loader to help setup the antivirus
     *
     * * copies the necessary files from the package to the installation folder
     * * loads the Antivirus library in the system
     * * tells to the Antivirus library where the copied files are
     */
    static {
        AntivirusUtils.setupAntivirus(App.getContext());
        // tries to load the antivirus library
        try {
            System.loadLibrary(AntivirusUtils.LIBRARY_NAME);
        } catch (UnsatisfiedLinkError e) {
            Log.e(TAG, "couldn't load antivirus library");
        }
        AntivirusUtils.setEnginePaths(App.getContext());
    }

    /**
     * Antivirus class that is the glue between java code and JNI code
     */
    public Antivirus() {
        // initialize the engine
        initialize();

        // ensure that the JNI part knows about the methods in the java side
        loadJavaClassToJNI();

        // register for a context pointer it is used with all calls on the native side from now on
        // this function also sets up the callback that sends scan results back to java code
        threadContextPointer = registerScanner(MAVAPI_VERSION);

        // a thread pool executor to deal with the runnable that performs the task of scanning
        singleThreadExecutor = Executors.newSingleThreadExecutor();
    }

    /**
     * gets the virus definitions file version
     * @return the date of the definitions
     */
    public String getVDFVersion() {
        return threadContextPointer != 0 ? getVDFSignatureDate(threadContextPointer) : "";
    }

    /**
     * gets the scanning engine version
     * @return version number
     */
    public String getEngineVersion() {
        return threadContextPointer != 0 ? getEngineVersion(threadContextPointer) : "";
    }

    /**
     * posts a scanning request to the native side
     * @param path path on the device to scan
     */
    public void scanPath(final String path) {
        singleThreadExecutor.execute(new Runnable() {
            @Override
            public void run() {
                try {
                    // start a package scan with the current generated context
                    Log.i(TAG, "AV:scan " + path);
                    scan(path, threadContextPointer);
                }catch (Exception e) {
                    Log.e(TAG, e.getMessage());
                }
            }
        });
    }

    /**
     * called from JNI - do not remove
     *
     * method is registered in the JNI glue code and is called when the scan of a file is finished with the
     * result set in ScannerCallback
     */
    @SuppressWarnings("unused")
    public synchronized void onScanCallback(int callbackState, String path, ScannerCallback callbackData)
    {
        switch (callbackState) {
            case REPORT_FILE_STATUS:
                try {
                    // post the result back to the UI thread to be processed there
                    Intent scanResultsIntent = new Intent(ACTION_SCAN_FINISHED);
                    scanResultsIntent.putExtra(EXTRA_PATH, path);
                    scanResultsIntent.putExtra(EXTRA_SCAN_RESULT, callbackData);
                    LocalBroadcastManager.getInstance(App.getContext()).sendBroadcast(scanResultsIntent);
                } catch (Exception e) {
                    Log.e(TAG, e.getMessage());
                }
                break;
        }
    }

    @Override
    protected void finalize() throws Throwable {
        // make sure that when the system calls finalize on this object we destroy the current scan context on the native side
        // (might result in memory leaks otherwise)
        if(threadContextPointer != 0) {
            int result = terminate(threadContextPointer);
            if(result == 0)
                threadContextPointer = 0;
            Log.i(TAG, "antivirus engine closed :: " + result);
        }
        super.finalize();
    }

    /**
     * tell to the native side where are the components of the scanning engine installed on the current device
     */
    public static void setEngineComponents(String enginePath, String libraryPath, String tempPath, String updatePath) {
        setEngineResourcePath(enginePath, libraryPath, tempPath, updatePath);
    }

    public long registerScanner() {
        return registerScanner(MAVAPI_VERSION);
    }



    /**
     * ********************************************************
     * native stuff
     * *********************************************************
     */
    private synchronized native int initialize();

    private native void loadJavaClassToJNI();

    private native long registerScanner(int mavapiVersionControl);

    private synchronized native int terminate(long threadContextPointer);

    private native int scan(String path, long threadContextPointer);

    private native int abortScanning(long threadContextPointer);

    private native String getVDFSignatureDate(long threadContextPointer);

    private native String getEngineVersion(long threadContextPointer);

    public native int terminateScanner(long threadContextPointer);

    private static native void setEngineResourcePath(String enginePath, String libraryPath, String tempPath, String updatePath);
    /************************************************************
     * native stuff
     ************************************************************/
}
