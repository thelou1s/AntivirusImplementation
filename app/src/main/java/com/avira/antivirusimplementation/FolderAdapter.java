package com.avira.antivirusimplementation;

import android.content.Context;
import android.text.TextUtils;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.TextView;

import java.util.ArrayList;
import java.util.List;

/**
 * @author ovidiu.buleandra
 * @since 7/13/2015
 */
public class FolderAdapter extends BaseAdapter {

    LayoutInflater inflater;
    List<String> folderList;

    public FolderAdapter(Context context) {
        inflater = LayoutInflater.from(context);
        folderList = new ArrayList<>();
    }

    @Override
    public int getCount() {
        return folderList.size();
    }

    @Override
    public Object getItem(int position) {
        return position < getCount() ? folderList.get(position) : null;
    }

    @Override
    public long getItemId(int position) {
        return 0;
    }

    @Override
    public View getView(int position, View convertView, ViewGroup parent) {
        View view = convertView;

        if(view == null) {
            view = inflater.inflate(R.layout.list_item, parent, false);
        }

        final String folder = (String)getItem(position);
        final TextView tv = (TextView) view.findViewById(R.id.label);
        if(!TextUtils.isEmpty(folder)) {
            tv.setText(folder);
        } else {
            tv.setText("");
        }
        if(position == 0) {
            view.findViewById(R.id.divider).setVisibility(View.INVISIBLE);
        } else {
            view.findViewById(R.id.divider).setVisibility(View.VISIBLE);
        }

        return view;
    }

    public void setList(List<String> folderList) {
        this.folderList.clear();
        this.folderList.addAll(folderList);
        notifyDataSetChanged();
    }
}
