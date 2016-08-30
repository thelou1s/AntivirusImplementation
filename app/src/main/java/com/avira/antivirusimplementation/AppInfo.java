package com.avira.antivirusimplementation;

public class AppInfo {
    public String displayName;
    public String packageName;
    public String sourceDir;

    public AppInfo(String name, String pkg, String source) {
        displayName = name;
        packageName = pkg;
        sourceDir = source;
    }
}
