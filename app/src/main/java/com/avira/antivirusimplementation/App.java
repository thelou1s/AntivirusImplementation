package com.avira.antivirusimplementation;

import android.app.Application;

public class App extends Application {

    private static App INSTANCE;

    @Override
    public void onCreate() {
        super.onCreate();

        INSTANCE = this;
    }

    public static App getContext() {
        if(INSTANCE == null) {
            throw new RuntimeException("application instance is null");
        }
        return INSTANCE;
    }
}
