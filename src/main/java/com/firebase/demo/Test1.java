package com.firebase.demo;

import java.util.LinkedHashMap;
import java.util.Map;
import java.util.Random;
import com.firebase.net.thegreshams.firebase4j.model.FirebaseResponse;
import com.firebase.net.thegreshams.firebase4j.service.Firebase;

public class Test1 {
    
    public static void main(String[] args) throws Throwable {
        String firebase_baseUrl = "https://iot-pcschool.firebaseio.com/myhouse";
        String token = "5lXpVgfZlmpjCNR4YzIDMDrh29Mw7kAp3zzhnSC4";
        // create the firebase
        Firebase firebase = new Firebase(firebase_baseUrl, token);
        while (true) {
            // �զX���
            Map<String, Object> dataMap = new LinkedHashMap<>();
            dataMap.put("temp", new Random().nextInt(1000));
            dataMap.put("humd", new Random().nextInt(1000));
            dataMap.put("cdsValue", new Random().nextInt(1000));
            dataMap.put("ledOnOff", new Random().nextInt(1000));
            dataMap.put("distance", new Random().nextInt(1000));
            dataMap.put("pm25", new Random().nextInt(1000));
            // put, patch, post
            // �N��ƤW�Ǩ춳��
            FirebaseResponse response = firebase.patch(dataMap );
            // ���o�̷s���
            System.out.println(firebase.get("temp").getRawBody());
            System.out.println(firebase.get("humd").getRawBody());
            System.out.println(firebase.get("cdsValue").getRawBody());
            System.out.println(firebase.get("ledOnOff").getRawBody());
            System.out.println(firebase.get("distance").getRawBody());
            System.out.println(firebase.get("pm25").getRawBody());
        }
    }
}
