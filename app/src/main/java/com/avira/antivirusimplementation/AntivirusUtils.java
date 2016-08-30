package com.avira.antivirusimplementation;

import android.content.Context;
import android.content.res.AssetManager;
import android.util.Log;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

/**
 * @author ovidiu.buleandra
 *
 * some utility methods to deal with first time setup of the application
 *
 * main purpose is to copy the scanning engine stuff from the assets folder in the app package
 * to some folders created on the device at the path of installation
 */
public class AntivirusUtils {

    private static final String TAG = AntivirusUtils.class.getSimpleName();

    public static final String LIBRARY_FILENAME = "libantivirus.so";
    public static final String LIBRARY_NAME = "antivirus";
    private static final String TEMP_DIR = "/temp";
    private static final String UPDATE_DIR = "/update";
    private static final String LIBRARY_DIR = "/bin";
    private static final String ANTIVIRUS_SUBDIR = LIBRARY_DIR + "/" + LIBRARY_NAME;
    private static final String BACKUP_DIR = LIBRARY_DIR + "/backup";

    /**
     * copies libraries from the assets folder to the main application folder
     * @param context application context to get the current installation path of the application (internal memory of the device)
     */
    public static void setupAntivirus(Context context) {
        String dataDir = context.getApplicationInfo().dataDir;
        try {
            // make sure or the folders are created
            createFolder(dataDir + LIBRARY_DIR);
            createFolder(dataDir + TEMP_DIR);
            createFolder(dataDir + UPDATE_DIR);
            createFolder(dataDir + BACKUP_DIR);
            File antivirusDir = createFolder(dataDir + ANTIVIRUS_SUBDIR);

            if(antivirusDir == null) {
                Log.e(TAG, "setup antivirus folders failed");
                return;
            }

            // copy all the files from the assets folder to the freshly created internal folders
            int filesNo = antivirusDir.list().length;
            AssetManager assetManager = context.getAssets();
            String[] filesList = assetManager.list(LIBRARY_NAME);
            if(filesList.length != filesNo) {
                for (String engineFile : filesList) {
                    InputStream in;
                    OutputStream out;
                    String configFilePath;

                    in = assetManager.open(LIBRARY_NAME + "/" + engineFile);
                    configFilePath = antivirusDir.getAbsolutePath() + "/" + engineFile;

                    out = new FileOutputStream(configFilePath);
                    copyFile(in, out);
                    out.flush();
                    in.close();
                    out.close();
                }
            }


        } catch (IOException e) {
            Log.e(TAG, "I/O error " + e.getMessage());
        }


    }

    /**
     * tell to the native side where we copied the files to make sure that the libraries and virus definitions database is loaded correctly
     *
     * @param context
     */
    public static void setEnginePaths(Context context) {
        String dataDir = context.getApplicationInfo().dataDir;
        Antivirus.setEngineComponents(LIBRARY_NAME, dataDir + LIBRARY_DIR, dataDir + TEMP_DIR, dataDir + UPDATE_DIR);
    }

    /**
     * utility method to create a folder
     *
     * @param path full path to create
     * @return {@link File} object of the folder just created
     * @throws IOException
     */
    private static File createFolder(String path) throws IOException {
        File file = new File(path);
        if(!file.exists()) {
            if(!file.mkdir()) {
                throw new IOException("couldn't create folder '" + path + "'");
            }
        }
        return file;
    }

    /**
     * utility method to copy a file from one stream to another
     *
     * @param in
     * @param out
     * @throws IOException
     */
    private static void copyFile(InputStream in, OutputStream out) throws IOException
    {
        byte[] buffer = new byte[1024];
        int read;
        while ((read = in.read(buffer)) != -1)
        {
            out.write(buffer, 0, read);
        }
    }
}
