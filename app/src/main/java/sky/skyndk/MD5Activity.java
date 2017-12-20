package sky.skyndk;

import android.os.Bundle;
import android.widget.Button;
import android.widget.TextView;

import java.util.HashMap;

import butterknife.BindView;
import butterknife.OnClick;
import sky.core.SKYActivity;
import sky.core.SKYBuilder;
import sky.core.SKYHelper;
import sky.core.SKYIDisplay;

/**
 * @author sky
 * @date Created on 2017-12-17 下午10:01
 * @version 1.0
 * @Description MD5Activity - 描述
 */
public class MD5Activity extends SKYActivity<MD5Biz> {

	@BindView(R.id.tv_content) TextView	tvContent;

	@BindView(R.id.btn_md5) Button		btnMd5;


	public static final void intent() {
		SKYHelper.display(SKYIDisplay.class).intent(MD5Activity.class);
	}

	@Override protected SKYBuilder build(SKYBuilder initialSKYBuilder) {
		initialSKYBuilder.layoutId(R.layout.activity_md5);
		return initialSKYBuilder;
	}

	@Override protected void initData(Bundle savedInstanceState) {

	}

	@OnClick(R.id.btn_md5) public void onBtnMd5Clicked() {
//	    tvContent.setText(MainActivity.md5(new HashMap<String, String>()));
    }
}