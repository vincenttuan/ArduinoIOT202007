package com.firebase.patch;

import com.firebase.net.thegreshams.firebase4j.model.FirebaseResponse;
import com.firebase.net.thegreshams.firebase4j.service.Firebase;
import java.util.LinkedHashMap;
import java.util.Map;

public class PatchToMyHouse {
    private static Firebase firebase = null;
    static {
        String firebase_baseUrl = "https://iot-pcschool.firebaseio.com/";
        String token = "5lXpVgfZlmpjCNR4YzIDMDrh29Mw7kAp3zzhnSC4";
        try {
            firebase = new Firebase(firebase_baseUrl, token);
        } catch (Throwable e) {
            System.out.println("建立 firebase 失敗");
            e.printStackTrace();
        }
    }

    public static void patch(String forder, String temp, String humd, String cdsValue, String ledOnOff, String distance, String pm25, String servoDegree) {
        Map<String, Object> dataMap = new LinkedHashMap<>();
        dataMap.put(forder + "/temp", Double.parseDouble(temp));
        dataMap.put(forder + "/humd", Double.parseDouble(humd));
        dataMap.put(forder + "/cdsValue", Integer.parseInt(cdsValue));
        dataMap.put(forder + "/ledOnOff", Integer.parseInt(ledOnOff));
        dataMap.put(forder + "/distance", Integer.parseInt(distance));
        dataMap.put(forder + "/pm25", pm25);
        dataMap.put(forder + "/servoDegree", Integer.parseInt(servoDegree));
        try {
            // put, patch, post
            FirebaseResponse response = firebase.patch(dataMap);
        } catch (Throwable e) {
            System.out.println("上傳失敗");
            e.printStackTrace();
        }
    }
    public static String get(String forder, String name) {
        try {
            return firebase.get(forder + "/" + name).getRawBody();
        } catch (Throwable e) {
            return null;
        }
    }
    public static void set(String forder, String name, Object value) {
        try {
            Map<String, Object> dataMap = new LinkedHashMap<>();
            dataMap.put(forder + "/" + name, value);
            FirebaseResponse response = firebase.patch(dataMap);
        } catch (Throwable e) {
            
        }
    }
}
