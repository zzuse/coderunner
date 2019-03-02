import java.lang.reflect.InvocationHandler;  
import java.lang.reflect.Method;  
import java.lang.reflect.Proxy;  
 
//抽象主题类,这里不能用abstract抽象类，一定要是interface  
interface AbstractSubject {  
	public abstract void request();  
}  
 
// 真实主题类，即被代理类  
class RealSubject implements AbstractSubject {  
	public void request() {  
		System.out.println("RealSubject's request() ...");  
	}  
}  
 
// 动态代理类，实现InvocationHandler接口  
class DynamicProxy implements InvocationHandler {  
 
	// 被代理类的实例  
	Object obj = null;  
 
	// 将被代理者的实例传进动态代理类的构造函数中  
	public DynamicProxy(Object obj) {  
		this.obj = obj;  
	}  
 
	/**  
	 * 覆盖InvocationHandler接口中的invoke()方法  
	 *   
	 * 更重要的是，动态代理模式可以使得我们在不改变原来已有的代码结构  
	 * 的情况下，对原来的“真实方法”进行扩展、增强其功能，并且可以达到  
	 * 控制被代理对象的行为，下面的before、after就是我们可以进行特殊  
	 * 代码切入的扩展点了。  
	 */ 
	public Object invoke(Object proxy, Method method, Object[] args)  
			throws Throwable {  
		/*  
		 * before ：doSomething();  
		 */ 
		System.out.println("开始事务2");
		Object result = method.invoke(this.obj, args);  
		  
		/*  
		 * after : doSomething();  
		 */ 
		System.out.println("提交事务2");
		return result;  
	}  
}  
 
// 测试类  
public class DynamicProxyClient {  
	public static void main(String[] args) {  
 
		// 被代理类的实例  
		AbstractSubject realSubject = new RealSubject();  
 
		// 获得被代理类的类加载器，使得JVM能够加载并找到被代理类的内部结构，以及已实现的interface  
		ClassLoader loader = realSubject.getClass().getClassLoader();  
 
		// 获得被代理类已实现的所有接口interface,使得动态代理类的实例  
		Class<?>[] interfaces = realSubject.getClass().getInterfaces();  
 
		// 用被代理类的实例创建动态代理类的实例，用于真正调用处理程序  
		InvocationHandler handler = new DynamicProxy(realSubject);  
 
		/*  
		 * loader : 被代理类的类加载器  
		 * interfaces ：被代理类已实现的所有接口，而这些是动态代理类要实现的接口列表  
		 * handler ： 用被代理类的实例创建动态代理类的实例，用于真正调用处理程序  
		 *   
		 * return ：返回实现了被代理类所实现的所有接口的Object对象，即动态代理，需要强制转型  
		 */ 
		//获得代理的实例  
		AbstractSubject proxy = (AbstractSubject) Proxy.newProxyInstance(  
				loader, interfaces, handler);  
 
		proxy.request();  
		//打印出该代理实例的名称  
		System.out.println(proxy.getClass().getName());  
	}  
} 