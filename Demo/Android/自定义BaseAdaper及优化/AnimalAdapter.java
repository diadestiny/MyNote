package com.example.day01;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.ImageView;
import android.widget.TextView;

import java.util.LinkedList;

public class AnimalAdapter extends BaseAdapter {

    private LinkedList<Animal> mData;
    private Context mContext;


    public AnimalAdapter(LinkedList<Animal> mData,Context mContext) {
        super();
        this.mContext=mContext;
        this.mData = mData;
    }

    @Override
    public int getCount() {
        return mData.size();
    }

    @Override
    public Object getItem(int position) {
        return null;
    }

    @Override
    public long getItemId(int position) {
        return 0;
    }

    @Override
    public View getView(int position, View convertView, ViewGroup parent) {
        ViewHolder holder = null;

        if(convertView==null){
            convertView = LayoutInflater.from(mContext).inflate(R.layout.list_item,parent,false);
            holder = new ViewHolder();
            holder.img_con = convertView.findViewById(R.id.tupian);
            holder.txt_aName = convertView.findViewById(R.id.name);
            holder.txt_aSpeak = convertView.findViewById(R.id.says);
            convertView.setTag(holder); //将Holder存储到convertView中
        }else{
            holder = (ViewHolder) convertView.getTag();
        }

        holder.img_con.setBackgroundResource(mData.get(position).getaIcon());
        holder.txt_aName.setText(mData.get(position).getaName());
        holder.txt_aSpeak.setText(mData.get(position).getaSpeak());
        return convertView;
    }

    static class ViewHolder{
        ImageView img_con;
        TextView txt_aName;
        TextView txt_aSpeak;
    }
}
