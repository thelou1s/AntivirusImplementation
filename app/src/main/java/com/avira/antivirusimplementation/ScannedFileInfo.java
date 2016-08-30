package com.avira.antivirusimplementation;

import android.os.Parcel;
import android.os.Parcelable;

import java.util.Collection;
import java.util.HashMap;

public class ScannedFileInfo implements Parcelable {
    private String mName;
    private String mPath;
    private int mLevel;
    private int mType;
    private HashMap<String, MalwareInfo> mMalwareInfoList;

    public ScannedFileInfo(String name, String path, int level, int type) {
        mName = name;
        mPath = path;
        mLevel = level;
        mType = type;
    }

    public void addMalwareInfo(String name, String appFlags, String message, String type) {
        if (mMalwareInfoList == null) {
            mMalwareInfoList = new HashMap<String, MalwareInfo>();
        }

        mMalwareInfoList.put(name, new MalwareInfo(name, appFlags, message, type));
    }

    public Collection<MalwareInfo> getMalwareInfoList() {
        Collection<MalwareInfo> result = null;
        if (mMalwareInfoList != null) {
            result = mMalwareInfoList.values();
        }

        return result;
    }

    private ScannedFileInfo(Parcel in) {
        mName = in.readString();
        mPath = in.readString();
        mLevel = in.readInt();
        mType = in.readInt();

        mMalwareInfoList = new HashMap<String, MalwareInfo>();
        int arraySize = in.readInt();
        for (int i = 0; i < arraySize; i++) {
            mMalwareInfoList.put(in.readString(), (MalwareInfo) in.readParcelable(MalwareInfo.class.getClassLoader()));
        }
    }

    public String getName() {
        return mName;
    }

    public String getPath() {
        return mPath;
    }

    public int getLevel() {
        return mLevel;
    }

    public int getType() {
        return mType;
    }

    @Override
    public int describeContents() {
        return 0;
    }

    @Override
    public void writeToParcel(Parcel dest, int flags) {
        dest.writeString(mName);
        dest.writeString(mPath);
        dest.writeInt(mLevel);
        dest.writeInt(mType);

        if (mMalwareInfoList != null) {
            dest.writeInt(mMalwareInfoList.size());
            for (MalwareInfo malwareInfo : mMalwareInfoList.values()) {
                dest.writeString(malwareInfo.getName());
                dest.writeParcelable(malwareInfo, 0);
            }
        } else {
            dest.writeInt(0);
        }
    }

    /*
     * Interface that must be implemented and provided as a public CREATOR field that generates instances of your
     * Parcelable class from a Parcel.
     */
    public static final Parcelable.Creator<ScannedFileInfo> CREATOR = new Parcelable.Creator<ScannedFileInfo>() {
        /*
         * (non-Javadoc)
         *
         * @see android.os.Parcelable.Creator#createFromParcel(android.os.Parcel)
         */
        @Override
        public ScannedFileInfo createFromParcel(Parcel in) {
            return new ScannedFileInfo(in);
        }

        /*
         * (non-Javadoc)
         *
         * @see android.os.Parcelable.Creator#newArray(int)
         */
        @Override
        public ScannedFileInfo[] newArray(int size) {
            return new ScannedFileInfo[size];
        }
    };
}