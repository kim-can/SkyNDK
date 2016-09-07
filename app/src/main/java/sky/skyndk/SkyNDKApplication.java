package sky.skyndk;

import android.app.Application;

import jc.sky.ISKYBind;
import jc.sky.SKYHelper;
import jc.sky.modules.SKYModulesManage;
import jc.sky.modules.methodProxy.SKYMethods;
import retrofit2.Retrofit;

/**
 * @创建人 sky
 * @创建时间 16/9/7 上午10:39
 * @类描述
 */
public class SkyNDKApplication extends Application implements ISKYBind {

	@Override public void onCreate() {
		super.onCreate();
		SKYHelper.bind(this);
	}

	@Override public boolean isLogOpen() {
		return true;
	}

	@Override public Retrofit getRestAdapter(Retrofit.Builder builder) {
		builder.baseUrl("http://www.baidu.com");
		return builder.build();
	}

	@Override public SKYMethods getMethodInterceptor(SKYMethods.Builder builder) {
		return builder.build();
	}

	@Override public SKYModulesManage getModulesManage() {
		return new SKYModulesManage(this);
	}
}
