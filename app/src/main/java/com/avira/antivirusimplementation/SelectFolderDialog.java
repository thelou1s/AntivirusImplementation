package com.avira.antivirusimplementation;

import android.graphics.drawable.ColorDrawable;
import android.os.AsyncTask;
import android.os.Bundle;
import android.os.Environment;
import android.support.v4.app.DialogFragment;
import android.support.v4.app.FragmentManager;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.view.Window;
import android.widget.AdapterView;
import android.widget.ListView;
import android.widget.TextView;

import java.io.File;
import java.lang.ref.WeakReference;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

/**
 * @author ovidiu.buleandra
 * @since 7/13/2015
 */
public class SelectFolderDialog extends DialogFragment implements View.OnClickListener, AdapterView.OnItemClickListener {

    ListView folderList;
    FolderAdapter folderAdapter;
    File sdCard;
    File currentPath;
    TextView pathView;
    SelectFolderInterface callback;

    public interface SelectFolderInterface {
        void onPathSelected(String path);
    }

    public void show(FragmentManager fragmentManager, SelectFolderInterface callback) {
        show(fragmentManager, SelectFolderDialog.class.getSimpleName());
        this.callback = callback;
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setCancelable(true);
        setStyle(STYLE_NO_TITLE, R.style.DialogNoTitle);
        setRetainInstance(true);

        if(!Environment.getExternalStorageState().equals(Environment.MEDIA_MOUNTED)) {
            sdCard = null;
        } else {
            sdCard = Environment.getExternalStorageDirectory();
        }

    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        final View view = inflater.inflate(R.layout.dialog_layout, container, false);

        Window window = getDialog().getWindow();
        window.setBackgroundDrawable(new ColorDrawable(0));

        pathView = (TextView) view.findViewById(R.id.path);

        view.findViewById(R.id.left_button).setOnClickListener(this);
        view.findViewById(R.id.right_button).setOnClickListener(this);

        folderList = (ListView) view.findViewById(R.id.list);
        folderAdapter = new FolderAdapter(getActivity());

        folderList.setAdapter(folderAdapter);
        folderList.setOnItemClickListener(this);

        if(sdCard != null) {

            currentPath = new File(sdCard.getPath());
            updatePathText();
            new ListDirsTask(folderAdapter, sdCard, true).execute();

        }

        return view;
    }

    @Override
    public void onClick(View v) {
        switch (v.getId()) {
            case R.id.left_button:
                dismiss();
                break;
            case R.id.right_button:
                if (callback != null) {
                    callback.onPathSelected(currentPath.getAbsolutePath());
                }
                dismiss();
                break;
        }
    }

    @Override
    public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
        String selectedFolder = (String)folderAdapter.getItem(position);
        if(selectedFolder.equals("..")) {
            currentPath = currentPath.getParentFile();
        } else {
            currentPath = new File(currentPath, selectedFolder);
        }

        updatePathText();
        new ListDirsTask(folderAdapter, currentPath, false).execute();
    }

    private void updatePathText() {
        pathView.setText(currentPath.getAbsolutePath());
    }

    private static class ListDirsTask extends AsyncTask<Void, Void, List<String>> {

        WeakReference<FolderAdapter> adapterRef;
        File folder;
        boolean isRoot;

        public ListDirsTask(FolderAdapter adapter, File root, boolean isRoot) {
            adapterRef = new WeakReference<>(adapter);
            folder = root;
            this.isRoot = isRoot;
        }

        @Override
        protected List<String> doInBackground(Void... params) {
            final List<String> result = new ArrayList<>();

            String[] files = folder.list();

            for(String fileName : files) {
                if(fileName.startsWith(".")) {
                    continue;
                }
                final File file = new File(folder, fileName);
                if(file.isDirectory()) {
                    result.add(fileName);
                }
            }

            Collections.sort(result);
            if(!isRoot) {
                result.add(0, "..");
            }

            return result;
        }

        @Override
        protected void onPostExecute(List<String> result) {
            if(adapterRef != null) {
                FolderAdapter adapter = adapterRef.get();
                if(adapter != null) {
                    adapter.setList(result);
                }
            }
        }
    }
}
