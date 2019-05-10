package com.diadestiny.test002;

public class Test1 {
	public static void main(String [] args) {
		Caller caller =new Caller();
		caller.setCallFunc(new MyCallInterface() {
			
			@Override
			public void printName() {
				System.out.println("This is the client printName method");
				
			}
		});
		caller.call();
	}
}
