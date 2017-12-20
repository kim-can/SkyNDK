package sky.skyndk;

import android.os.Bundle;
import android.util.LongSparseArray;
import android.util.SparseArray;
import android.widget.Button;
import android.widget.TextView;

import java.util.HashMap;
import java.util.LinkedHashMap;

import butterknife.BindView;
import butterknife.OnClick;
import sky.core.SKYActivity;
import sky.core.SKYBuilder;
import sky.core.SKYHelper;
import sky.core.SKYIDisplay;

/**
 * @author sky
 * @date Created on 2017-12-16 下午4:51
 * @version 1.0
 * @Description MainActivity - 描述
 */
public class MainActivity extends SKYActivity<MainBiz> {

	@BindView(R.id.tv_content) TextView	tvContent;

	@BindView(R.id.btn_md5) Button		btnMd5;

	@BindView(R.id.btn_string) Button	btnString;

	public static final void intent() {
		SKYHelper.display(SKYIDisplay.class).intent(MainActivity.class);
	}

	static {
		System.loadLibrary("native-lib");
	}

	@Override protected SKYBuilder build(SKYBuilder initialSKYBuilder) {
		initialSKYBuilder.layoutId(R.layout.activity_main);
		return initialSKYBuilder;
	}

	HashMap<String, String> hashMap = new HashMap<>();

	/**
	 *
	 date=2017-12-21&endCityCode=SHA&isNative=1&latitude=39.949946&longtitude=116.414512&startCityCode=BJS&timestamp=1513734961524

	 * @param savedInstanceState
	 */
	@Override protected void initData(Bundle savedInstanceState) {
		hashMap.put("endCityCode", "SHA");
		hashMap.put("longtitude", "116.414512");
		hashMap.put("isNative", "1");
		hashMap.put("date", "2017-12-21");
		hashMap.put("timestamp", "1513734961524");
		hashMap.put("latitude", "39.949946");
		hashMap.put("startCityCode", "BJS");
	}

	public native static String stringFromJNI();

	public native static String md5(HashMap<String, String> hashMap);

//	public static native String md5(String hashMap);

	@OnClick(R.id.btn_md5) public void onBtnMd5Clicked() {
		// tvContent.setText(md5());
		MD5Activity.intent();
	}

	@OnClick(R.id.btn_string) public void onBtnStringClicked() {
		tvContent.setText(md5(hashMap));
	}
}