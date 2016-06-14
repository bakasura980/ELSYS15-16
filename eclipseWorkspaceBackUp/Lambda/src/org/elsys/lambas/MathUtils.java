package org.elsys.lambas;

import java.math.BigDecimal;
import java.util.ArrayList;
import java.util.List;

public class MathUtils {

	public static double integrate(Integrable function, double begin, double end, int deltas) {

		double interval = (end - begin) / deltas;
		double sum = 0;
		for (; begin < end; begin += interval) {
			sum += interval * function.call(begin);
		}
		return sum;
	}
	
	public static void main(String[] args) {
		List<Double> result = new ArrayList<>();
		//za da raboti tova^,interface trqbva da ima 1 method
		result.add(MathUtils.integrate(x -> x * x, -2, 15.5, 1000));
		
		/* ako iskame interface s pove4e metodi
		 * 
		result.add(MathUtils.integrate(new Integrable(){
			public double call(double y) {
				return y*y;
			};
		}, -2, 15.5, 1000));
		*/
		
		result.add(MathUtils.integrate(x -> Math.sin(x), 0, Math.PI*2, 1000));
		//Method Reference of a static method
		result.add(MathUtils.integrate(Math::sin, 0, Math.PI*2, 1000));
		result.forEach(System.out::println);
		//method reference of an instance method
		result.stream().map(Double::intValue).forEach(System.out::println);
		//.map(x-> new BigDecimal(x) equivalent to : ->
		result.stream().map(BigDecimal::new).forEach(System.out::println);;
	}
}
