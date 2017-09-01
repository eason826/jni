package smart.com.jnitest;

import android.app.Activity;
import android.os.Bundle;
import android.widget.TextView;
import smart.com.jnitest.myJNI;

public class MainActivity extends Activity {
    
	private TextView text;
	static{
	System.loadLibrary("myjni");
	}

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
	myJNI jni = new myJNI();
	int sum = jni.Add(100,150);
	text = (TextView)findViewById(R.id.showContent);
	text.setText("you are:"+sum);
    }
}
