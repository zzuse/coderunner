#!/usr/bin/env python3

import random
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
	
def check_speed(time_gap, speed_gap, total_time, min_speed, max_speed):
	
	times = (int) (total_time / time_gap)
	
	data_array = np.empty(times)
	weights_array = np.empty(times)
	weights_array.fill(1 / times)
	
	for i in range(0, times):
		if (speed_gap < 1):
			data_array[i] = random.random() * max_speed
		else:
			data_array[i] = random.randint(0, max_speed/speed_gap) * speed_gap
	
	data_frame = pd.DataFrame(data_array)
	print(data_frame)
	bin_range = np.arange(0, 200, speed_gap)
	data_frame.plot(kind='hist', bins = bin_range, legend=False)  # frequence
	data_frame.plot(kind='hist', bins = bin_range, legend=False, weights=weights_array).set_ylabel("Probability")  # probability
	plt.show()
	
check_speed(1, 5, 60, 0, 200)