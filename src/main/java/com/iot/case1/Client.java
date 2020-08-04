package com.iot.case1;

public class Client {
    // 接收 Arduino 的資料 
    private static Callback callback = new Callback() {
        @Override
        public void getValue(String fulldata) {
            // 檢查資料是否有包含 #
            if(!fulldata.contains("#")) {
                return;
            }
            // 去除 #
            fulldata = fulldata.replaceAll("#", "");
            // 切割資料
            String[] array = fulldata.split(",");
            // 切割後資料欄位數
            //System.out.println(array.length);
            // 確認合法資料欄位數 (假設=2)
            if(array.length != 2){
                return;
            }
            // 分析資料
            System.out.printf("溫度: %.1f 濕度: %.1f\n", Double.parseDouble(array[0]), Double.parseDouble(array[1]));
            System.out.printf("溫度: %s 濕度: %s\n", array[0], array[1]);
            
        }
    };
    
    // 主程式
    public static void main(String[] args ) throws Exception {
          (new TwoWaySerialComm(callback)).connect("COM14");
          
    }
}
