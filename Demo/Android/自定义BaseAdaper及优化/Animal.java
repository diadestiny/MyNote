package com.example.day01;

public class Animal {
    private String aName;
    private String aSpeak;
    private int aIcon;

    public Animal(String aName, String aSpeak, int aIcon) {
        this.aIcon=aIcon;
        this.aName=aName;
        this.aSpeak=aSpeak;
    }

    public String getaName() {
        return aName;
    }

    public void setaName(String aName) {
        this.aName = aName;
    }

    public int getaIcon() {
        return aIcon;
    }

    public void setaIcon(int aIcon) {
        this.aIcon = aIcon;
    }

    public String getaSpeak() {
        return aSpeak;
    }

    public void setaSpeak(String aSpeak) {
        this.aSpeak = aSpeak;
    }
}
