class HelloWorld {
	public static void main(String[] args) throws InterruptedException {
		Thread myThread = new Thread() 
		{        
			public void run() 
			{          
				System.out.println("Hello from new thread");        
			}      
		};
		myThread.start();    
		Thread.yield();//if delete this line,will print main permernately
		System.out.println("Hello from main thread");
	    myThread.join();
	}
}