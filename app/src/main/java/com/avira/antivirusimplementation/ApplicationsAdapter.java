package com.avira.antivirusimplementation;

import android.content.Context;
import android.content.pm.PackageManager;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.TextView;

import java.util.List;


public class ApplicationsAdapter extends BaseAdapter {

    private List<AppInfo> list;
    private LayoutInflater inflater;
    private PackageManager packageManager;

    public ApplicationsAdapter(Context context, List<AppInfo> applicationsList) {
        list = applicationsList;
        inflater = LayoutInflater.from(context);
        packageManager = context.getPackageManager();
    }

    @Override
    public int getCount() {
        return list != null ? list.size() : 0;
    }

    @Override
    public Object getItem(int position) {
        return list != null ? list.get(position) : null;
    }

    @Override
    public long getItemId(int position) {
        return 0;
    }

    @Override
    public View getView(int position, View convertView, ViewGroup parent) {
        View view;

        if(convertView != null) {
            view = convertView;
        } else {
            view = inflater.inflate(R.layout.list_item_double, parent, false);
        }

        AppInfo info = (AppInfo) getItem(position);

        ((TextView)view.findViewById(android.R.id.text1)).setText(info.displayName);
        ((TextView)view.findViewById(android.R.id.text2)).setText(info.packageName);

        return view;
    }
}
