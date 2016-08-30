package com.avira.antivirusimplementation;

import android.app.AlertDialog;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageManager;
import android.content.res.Resources;
import android.os.AsyncTask;
import android.os.Bundle;
import android.support.v4.content.LocalBroadcastManager;
import android.support.v7.app.ActionBarActivity;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.ListAdapter;
import android.widget.ListView;
import android.widget.ProgressBar;
import android.widget.TextView;

import java.io.File;
import java.lang.ref.WeakReference;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.LinkedList;
import java.util.List;

/**
 * @author ovidiu.buleandra
 *
 * main activity presented to the user
 * uses an antivirus object to scan an application that the user chooses from the list of installed non-system apps
 *
 * for the purpose of testing install EICAR Antivirus test from the playstore (harmless app that holds a test virus signature)
 *
 */
public class AntivirusActivity extends ActionBarActivity implements View.OnClickListener{

    private static final String TAG = AntivirusActivity.class.getSimpleName();

    private ScanResultsReceiver scanResultsReceiver;

    private ProgressBar progress;
    private Button btnSelect, btnSelectFolder;
    private TextView txtSelectedApp, txtVersion, warning;
    private ListView resultsList;
    private List<AppInfo> listOfApplications;
    private ScanFolderTask scanFolderTask;
    private ScanResultsAdapter resultsAdapter;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_antivirus);

        // ui stuff
        btnSelect = (Button) findViewById(R.id.btn_select_app);
        btnSelectFolder = (Button) findViewById(R.id.btn_select_folder);
        txtSelectedApp = (TextView) findViewById(R.id.scan_target);
        resultsList = (ListView) findViewById(R.id.results);
        warning = (TextView) findViewById(R.id.warning);
        txtVersion = (TextView) findViewById(R.id.txt_version);
        progress = (ProgressBar) findViewById(R.id.progress);

        btnSelect.setOnClickListener(this);
        btnSelectFolder.setOnClickListener(this);

        txtSelectedApp.setText("");

        listOfApplications = new ArrayList<>();

        // display some info about the scan engine and virus definitions
        txtVersion.setText(String.format("Virus Definitions %s\nEngine version %s",
                Antivirus.getInstance().getVDFVersion(),
                Antivirus.getInstance().getEngineVersion()));

        resultsAdapter = new ScanResultsAdapter(this, warning);
        resultsList.setAdapter(resultsAdapter);

        scanResultsReceiver = new ScanResultsReceiver();
        scanFolderTask = new ScanFolderTask();
    }

    @Override
    protected void onResume() {
        super.onResume();
        listOfApplications.clear();
        new LoadApplicationsTask(this, listOfApplications).execute();

        LocalBroadcastManager.getInstance(this).registerReceiver(scanResultsReceiver,
                new IntentFilter(Antivirus.ACTION_SCAN_FINISHED));
    }

    @Override
    protected void onPause() {
        super.onPause();
        if(scanFolderTask != null) {
            scanFolderTask.cancel(true);
        }
        LocalBroadcastManager.getInstance(this).unregisterReceiver(scanResultsReceiver);
    }

    @Override
    public void onClick(View v) {
        int id = v.getId();
        switch (id) {
            case R.id.btn_select_app:
                final ListAdapter adapter = new ApplicationsAdapter(this, listOfApplications);
                AlertDialog.Builder builder = new AlertDialog.Builder(this);
                builder.setAdapter(adapter, new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        AppInfo selectedApp = (AppInfo)adapter.getItem(which);
                        txtSelectedApp.setText(selectedApp.displayName);
                        resultsAdapter.clear();
                        startScan(selectedApp.sourceDir);
                    }
                });
                builder.create().show();
                break;
            case R.id.btn_select_folder:
                new SelectFolderDialog().show(getSupportFragmentManager(), new SelectFolderDialog.SelectFolderInterface() {
                    @Override
                    public void onPathSelected(String path) {
                        txtSelectedApp.setText(path);

                        scanFolderTask = new ScanFolderTask();
                        resultsAdapter.clear();
                        scanFolderTask.execute(path);
                    }
                });
                break;
        }
    }


    private void startScan(String targetDir) {
        Antivirus.getInstance().scanPath(targetDir);
    }

    private class ScanResultsReceiver extends BroadcastReceiver {
        @Override
        public void onReceive(Context context, Intent intent) {
            String scannedPath = intent.getStringExtra(Antivirus.EXTRA_PATH);
            ScannerCallback callbackData = intent.getParcelableExtra(Antivirus.EXTRA_SCAN_RESULT);
            Log.i(TAG, "AV:ScanResultsReceiver " + scannedPath + " > " + callbackData);
            resultsAdapter.addDetection(scannedPath, callbackData);
        }
    }

    private static class ScanFolderTask extends AsyncTask<String, Void, Void> {
        @Override
        protected Void doInBackground(String... params) {
            String path = params[0];

            LinkedList<String> dirs = new LinkedList<>();
            dirs.push(path);

            while(dirs.size() > 0) {
                String currentDirPath = dirs.pop();
                File currentDir = new File(currentDirPath);
                String[] files = currentDir.list();
                if(files == null)
                    continue;
                for(String file: files) {
                    if(isCancelled()) {
                        return null;
                    }
                    File currentFile = new File(currentDirPath, file);
                    if(currentFile.isFile()) {
                        Antivirus.getInstance().scanPath(currentFile.getPath());
                    } else if(currentFile.isDirectory()) {
                        dirs.push(currentFile.getPath());
                    } // ignore all others
                }
            }

            return null;
        }
    }

    private static class LoadApplicationsTask extends AsyncTask<Void, AppInfo, Void> {
        private WeakReference<List<AppInfo>> weakRefList;
        private PackageManager packageManager;

        public LoadApplicationsTask(Context ctx, List<AppInfo> list) {
            weakRefList = new WeakReference<>(list);
            packageManager = ctx.getPackageManager();
        }

        @Override
        protected Void doInBackground(Void... params) {
            List<ApplicationInfo> listOfApplications = packageManager.getInstalledApplications(0);

            for(ApplicationInfo info : listOfApplications) {
                try {
                    if ((info.flags & ApplicationInfo.FLAG_SYSTEM) == 0) {
                        String name = info.loadLabel(packageManager).toString();
                        publishProgress(new AppInfo(name, info.packageName, info.publicSourceDir));
                    }
                } catch(Resources.NotFoundException e) {
                    Log.e(TAG, "error loading label " + e.getMessage());
                } catch (Exception e) {
                    Log.e(TAG, e.getMessage());
                }
            }

            return null;
        }

        @Override
        protected void onProgressUpdate(AppInfo... values) {
            List<AppInfo> list = weakRefList.get();

            if(list != null) {
                list.add(values[0]);
            }
        }

        @Override
        protected void onPostExecute(Void aVoid) {
            List<AppInfo> list = weakRefList.get();
            if(list != null) {
                Collections.sort(list, new Comparator<AppInfo>() {
                    @Override
                    public int compare(AppInfo lhs, AppInfo rhs) {
                        return lhs.displayName.compareTo(rhs.displayName);
                    }
                });
            }
        }
    }
}
