package sky.skyndk;

import jc.sky.core.Impl;
import jc.sky.core.SKYBiz;
import jc.sky.core.SKYIBiz;

/**
 * @创建人 sky
 * @创建时间 16/9/7 上午10:17
 * @类描述 一句话描述你的业务
 */
@Impl(MainBiz.class)
public interface IMainBiz extends SKYIBiz {

}

class MainBiz extends SKYBiz<IMainActivity> implements IMainBiz {

}