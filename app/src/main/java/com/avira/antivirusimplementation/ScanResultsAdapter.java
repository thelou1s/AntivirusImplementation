package com.avira.antivirusimplementation;

import android.content.Context;
import android.graphics.Color;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.TextView;

import java.util.ArrayList;
import java.util.Collection;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * @author ovidiu.buleandra
 * @since 7/14/2015
 */
public class ScanResultsAdapter extends BaseAdapter {

    List<ResultContainer> list = new ArrayList<>();
    LayoutInflater inflater;
    View emptyView;
    int normalColor, warningColor;

    public ScanResultsAdapter(Context context, View empty) {
        inflater = LayoutInflater.from(context);
        emptyView = empty;
        normalColor = context.getResources().getColor(R.color.gray);
        warningColor = Color.parseColor("#F05133");
    }

    public void clear() {
        list.clear();
        emptyView.setVisibility(View.VISIBLE);
        notifyDataSetChanged();
    }

    public void addDetection(String path, ScannerCallback data) {
        emptyView.setVisibility(View.INVISIBLE);
        boolean replaced = false;
        for(ResultContainer container : list) {
            if(container.path.equals(path)) {
                container.addData(data);
                replaced = true;
                break;
            }
        }
        if(!replaced) {
            list.add(new ResultContainer(path, data));
        }
        notifyDataSetChanged();
    }

    @Override
    public int getCount() {
        return list.size();
    }

    @Override
    public Object getItem(int position) {
        return position < getCount() ? list.get(position) : null;
    }

    @Override
    public long getItemId(int position) {
        return 0;
    }

    @Override
    public View getView(int position, View convertView, ViewGroup parent) {
        View view = convertView;
        if(view == null) {
            view = inflater.inflate(R.layout.list_item_double, parent, false);
        }

        final ResultContainer item = (ResultContainer)getItem(position);
        if(item == null) {
            return null;
        }

        ((TextView) view.findViewById(android.R.id.text1)).setText(item.path);
        TextView info =(TextView) view.findViewById(android.R.id.text2);
        info.setText(item.prettyInfo);
        info.setTextColor(item.data != null ? warningColor : normalColor);

        return view;
    }

    static class ResultContainer {
        public String path;
        public ScannerCallback data = null;
        public String prettyInfo;

        public ResultContainer(String newPath, ScannerCallback newData) {
            path = newPath;
            prettyInfo = "nothing found";
            addData(newData);
        }

        public void addData(ScannerCallback newData) {
            if(newData != null) {
                data = newData;
                processData();
            }
        }

        private void processData() {
            if (data != null) {
                final HashMap<String, ScannedFileInfo> infected = data.getInfectedFileInfoList();
                if (infected.size() > 0) {
                    StringBuilder sb = new StringBuilder();
                    for (Map.Entry<String, ScannedFileInfo> entry : infected.entrySet()) {
                        sb.append('\u25cf');
//                        sb.append(" ");
//                        sb.append(entry.getKey());
//                        sb.append('|');
                        Collection<MalwareInfo> malwareInfoList = entry.getValue().getMalwareInfoList();
                        boolean more = false;
                        for (MalwareInfo info : malwareInfoList) {
                            if(more) {
                                sb.append(':');
                            }
                            sb.append(info.getName());
                            more = true;
                        }
                        sb.append('\n');
                    }
                    prettyInfo = sb.toString();
                }
            }
        }
    }
}
