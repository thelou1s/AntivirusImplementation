package com.avira.antivirusimplementation;

import android.os.Parcel;
import android.os.Parcelable;

import java.text.DateFormat;
import java.util.Date;
import java.util.HashMap;
import java.util.Map;

public class ScannerCallback implements Parcelable {
    private final static String TIME_STAMP_FORMAT = "%s, %s";
    private ScannedFileInfo mFileInfo;

    /**
     * Every set of HashMap<String, ScannedFileInfo> represents a physical file inside the zip
     */
    private HashMap<String, ScannedFileInfo> mFileInfoList;
    private long mTimestamp;

    public ScannerCallback(String name, String path, int level, int type) {
        mFileInfo = new ScannedFileInfo(name, path, level, type);
        mFileInfoList = new HashMap<>();
        Date date = new Date();
        mTimestamp = date.getTime();
    }

    private ScannerCallback(Parcel in) {
        mTimestamp = in.readLong();
        mFileInfo = in.readParcelable(ScannedFileInfo.class.getClassLoader());
        mFileInfoList = new HashMap<>();
        int arraySize = in.readInt();
        for (int i = 0; i < arraySize; i++) {
            mFileInfoList.put(in.readString(),
                    (ScannedFileInfo) in.readParcelable(ScannedFileInfo.class.getClassLoader()));
        }
    }

    public ScannedFileInfo getFileInfo() {
        return mFileInfo;
    }

    public void addMalwareInfo(String filename, String filepath, int fileLevel, int fileType, String malwareName, String appFlags, String message, String type) {
        String processedDetectionDescription = malwareName;
        if (processedDetectionDescription != null) {
            ScannedFileInfo fileInfo = mFileInfoList.get(filename);
            if (fileInfo == null) {
                fileInfo = new ScannedFileInfo(filename, filepath, fileLevel, fileType);
                mFileInfoList.put(filename, fileInfo);
            }

            fileInfo.addMalwareInfo(malwareName, appFlags, message, type);
        }
    }

    public HashMap<String, ScannedFileInfo> getInfectedFileInfoList() {
        return mFileInfoList;
    }

    public String getTimeStamp() {
        DateFormat dateFormat = android.text.format.DateFormat.getDateFormat(App.getContext());

        DateFormat timeFormat = android.text.format.DateFormat.getTimeFormat(App.getContext());

        Date date = new Date(mTimestamp);
        return String.format(TIME_STAMP_FORMAT, timeFormat.format(date), dateFormat.format(date));
    }

    @Override
    public int describeContents() {
        return 0;
    }

    @Override
    public void writeToParcel(Parcel dest, int flags) {
        dest.writeLong(mTimestamp);
        dest.writeParcelable(mFileInfo, 0);
        dest.writeInt(mFileInfoList.size());
        for (Map.Entry<String, ScannedFileInfo> entry : mFileInfoList.entrySet()) {
            dest.writeString(entry.getKey());
            dest.writeParcelable(entry.getValue(), 0);
        }
    }

    /*
     * Interface that must be implemented and provided as a public CREATOR field that generates instances of your
     * Parcelable class from a Parcel.
     */
    public static final Parcelable.Creator<ScannerCallback> CREATOR = new Parcelable.Creator<ScannerCallback>() {
        @Override
        public ScannerCallback createFromParcel(Parcel in) {
            return new ScannerCallback(in);
        }

        @Override
        public ScannerCallback[] newArray(int size) {
            return new ScannerCallback[size];
        }
    };
}
