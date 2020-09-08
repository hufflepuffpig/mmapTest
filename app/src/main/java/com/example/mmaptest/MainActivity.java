package com.example.mmaptest;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
//    static {
//        System.loadLibrary("native-lib");
//    }
    static  MmapUtilsJNI mmapUtilsJNI = new MmapUtilsJNI();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = findViewById(R.id.sample_text);
        Button btn = findViewById(R.id.button);
        btn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                mmapUtilsJNI.init(getExternalFilesDir("").getAbsolutePath()+"/peoples.txt");
//                mmapUtilsJNI.setPeople("a",20);
//                mmapUtilsJNI.setPeople("b",21);
//                mmapUtilsJNI.setPeople("c",22);
//                mmapUtilsJNI.setPeople("d",23);
//                mmapUtilsJNI.setPeople("e",24);
//                mmapUtilsJNI.setPeople("f",25);
                Log.e("Hopelin", mmapUtilsJNI.getPeople(0));
                Log.e("Hopelin", mmapUtilsJNI.getPeople(1));
                Log.e("Hopelin", mmapUtilsJNI.getPeople(2));
                Log.e("Hopelin", mmapUtilsJNI.getPeople(3));
                Log.e("Hopelin", mmapUtilsJNI.getPeople(4));
                Log.e("Hopelin", mmapUtilsJNI.getPeople(5));
                Log.e("Hopelin", mmapUtilsJNI.getPeople(6));
                mmapUtilsJNI.close();
            }
        });
        Log.e("Hopelin", getExternalFilesDir("").getAbsolutePath());
        tv.setText(mmapUtilsJNI.printString("HHHHHHH"));
//        tv.setText(stringFromJNI());
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
//    public native String stringFromJNI();
}
