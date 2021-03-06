package com.github.stenzek.duckstation;

import android.app.Activity;
import android.content.Context;
import android.content.SharedPreferences;
import android.util.ArraySet;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.TextView;

import androidx.preference.PreferenceManager;

import java.util.Set;

public class GameList {
    private Context mContext;
    private GameListEntry[] mEntries;
    private ListViewAdapter mAdapter;

    public GameList(Context context) {
        mContext = context;
        mAdapter = new ListViewAdapter();
        mEntries = new GameListEntry[0];
    }

    public void refresh(boolean invalidateCache, boolean invalidateDatabase) {
        // Search and get entries from native code
        AndroidHostInterface.getInstance().refreshGameList(invalidateCache, invalidateDatabase);
        mEntries = AndroidHostInterface.getInstance().getGameListEntries();
        mAdapter.notifyDataSetChanged();
    }

    public int getEntryCount() {
        return mEntries.length;
    }

    public GameListEntry getEntry(int index) {
        return mEntries[index];
    }

    private class ListViewAdapter extends BaseAdapter {
        @Override
        public int getCount() {
            return mEntries.length;
        }

        @Override
        public Object getItem(int position) {
            return mEntries[position];
        }

        @Override
        public long getItemId(int position) {
            return position;
        }

        @Override
        public int getViewTypeCount() {
            return 1;
        }

        @Override
        public View getView(int position, View convertView, ViewGroup parent) {
            if (convertView == null) {
                convertView = LayoutInflater.from(mContext)
                        .inflate(R.layout.game_list_view_entry, parent, false);
            }

            mEntries[position].fillView(convertView);
            return convertView;
        }
    }

    public BaseAdapter getListViewAdapter() {
        return mAdapter;
    }
}
