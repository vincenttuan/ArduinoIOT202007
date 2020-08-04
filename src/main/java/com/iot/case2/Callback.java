package com.iot.case2;


public abstract class Callback {
    private boolean relayValue;
    public abstract void getValue(String fulldata);
    public void setRelayValue(boolean flag) {
        relayValue = flag;
    }
    public boolean getRelayValue() {
        return relayValue;
    }
}
