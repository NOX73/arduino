package ru.nox73.homeapp;

import android.os.AsyncTask;
import android.util.Log;

import org.apache.http.HttpResponse;
import org.apache.http.client.HttpClient;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.impl.client.DefaultHttpClient;

/**
 * Created by nox73 on 02.09.14.
 */
public class AquariumOnOffTask extends AsyncTask<String, Void, Void> {

    @Override
    protected Void doInBackground(String... params) {

        HttpClient httpclient = new DefaultHttpClient();
        try {
            HttpResponse response = httpclient.execute(new HttpGet("http://192.168.1.2:3000?pos="+params[0]));
        } catch (Exception e) {
            Log.e("HomeApp", e.getMessage());
        }

        return null;
    }
}
