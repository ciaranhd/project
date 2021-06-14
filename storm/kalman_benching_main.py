import numpy as np
from pylab import ylim, title, ylabel, xlabel
import matplotlib.pyplot as plt
from kalman import SingleStateKalmanFilter
import pandas as pd
from collections import defaultdict
import seaborn as sns

# ------------------------------------------- Filtering: PARAMETERS : (START) --------------------------------------
""" 
    The Parameters for the Filter are outlined below.
    
    Q: The Process Covariance weights the final Kalman Output either towards the actual measurement or Kalman
       Prediction. The lower this value is, for example, 0.005, the less noise/volatility in the output.
       You must use judgement when setting this variable. 
       
    A: Process Innovation: I tend to leave as 1 (has no affect). If >1 then the graph will drift upwards by the scaling 
       factor. 
       
    x: We make an arbitrary guess at the beginning. After a certain amount of data, the model increases to the correct
       value. This is similar to the Posterior in Bayesian Updating. 
       
    P: Again this is arbitrary and will update to the correct values after multiple data is passed into the Filter.

"""
# Initialise the Kalman Filter
A = 1       # No process innovation - use 1
C = 1       # Measurement
B = 0       # No control input
Q = 0.3     # Process covariance
R = 1       # Measurement covariance
x = 100     # Initial state_estimate
P = 1       # Initial covariance/ prob_estimate

# ------------------------------------------- Filtering: PARAMETERS : (END) --------------------------------------

real_time = False
if real_time:
    """ Probably Don't Need This. It was designed to update incoming SLM Data in Real Time With the Filter"""
    # This CSV will be extracted from the Cloud
    df = pd.read_csv('kalman_data.csv')
    col = df.columns
    # Previous State Estimate
    x = float(col[0])
    # Previous Probability Estimate
    P = float(col[1])

# Initialise The Kalman Object With Parameters
kalman_filter = SingleStateKalmanFilter(A, B, C, x, P, Q, R)

# Empty List For Kalman Filter Estimates
kalman_filter_estimates = []

# Need to read the incoming data for new iterations in real time.
if real_time:
    """ If Real_Time is True then read in real time data from the Crontab. Else Just Run all the
        data through the Filter. 
    """
    csv = 'kalman_real_time.csv'
else:
    csv = '16090_CSO_SLM_data.csv'

df = pd.read_csv(csv)
level_data = df["Level"]
time_stamp = df["Time/Date"]
Value = df["Value"]
OFlow = df["OFlow"]
kalman_filtered_data_dict = defaultdict()
kalman_filtered_data_dict["Time/Date"] = ["Level","Value","OFlow"]

# ------------------------------------------- Benching: View Distribution (START) --------------------------------------
""" 
    We First need to inspect the distribution of the data points to identify benching locations.
    Change show_distribution to True to view the plot. 
    Once Complete change this to False.
"""
df.Level = df.Level.round(1)
# Create Distribution
show_distribution = False
if show_distribution:
    sns.displot(df, x="Level")
    plt.show()
# ------------------------------------------- Benching: View Distribution ( END) ---------------------------------------



# ------------------------------------------- Benching: Benchng Tool (START) --------------------------------
""" 
    Change show_benching_locatinons to True to View data points that are most likely to be benching. 
"""



Benching_Tool = False
# Decide Count or Instances of a certain value appearing for which we wich to erase.
#This is a Threshold Value. The Higher the Count, the more likely benching is at this location.
count_to_erase = 50
if Benching_Tool:
    df_benching_loc = df['Level'].value_counts()
    df_benching_loc = df_benching_loc.to_frame()
    df_benching_loc.reset_index(level=0, inplace=True)
    df_benching_loc.rename(columns={'index': 'Levels'}, inplace=True)
    df_benching_loc.rename(columns={'Level': 'Count'}, inplace=True)
    # Choose Benching Corridors : Hint: Run show_distribution plot to identify benching regions

    df_benching_loc = df_benching_loc[((df_benching_loc['Levels'] >= 24.) & (df_benching_loc['Levels'] <= 26.5)) \
                                      | ((df_benching_loc['Levels'] >= 95) & (df_benching_loc['Levels'] <= 97))  \
                                      | ((df_benching_loc['Levels'] >= 95) & (df_benching_loc['Levels'] <= 97))  \
                                      | ((df_benching_loc['Levels'] >= 108) & (df_benching_loc['Levels'] <= 112))\
                                      | ((df_benching_loc['Levels'] >= 66) & (df_benching_loc['Levels'] <= 68))]
    df_benching_loc = df_benching_loc[(df_benching_loc['Count'] >= count_to_erase)]
    level_series = df['Level']
    for level_to_remove in df_benching_loc['Levels']:
        level_series = level_series.replace(level_to_remove, np.nan)
    df = df.assign(Level=level_series)
    #print(df)

    level_data = df["Level"]

# ------------------------------------------- Benching: View Benching Tool (END) --------------------------------








# ------------------------------------------- Filtering: MAIN : (START) --------------------------------------
# Simulate the data arriving sequentially
for i in range(len(level_data)):
    temp = []
    #print(f'level data before: {level_data[i]}')
    kalman_filter.step(0, level_data[i])

    kalman_prediction = round(kalman_filter.current_state(),2)
    #print(f'Prediction After: {kalman_prediction}')

    if kalman_prediction < 0:
        print("negative!!!!")
    # Negative Data Should be Zerod
    kalman_prediction = max(kalman_prediction,0)
    kalman_filter_estimates.append(kalman_prediction)

    temp.append(kalman_prediction)
    temp.append(Value[i])
    temp.append(OFlow[i])
    kalman_filtered_data_dict[time_stamp[i]] = temp

# kalman_filtered_data_dict should contain all of the filtered data.
#print(kalman_filtered_data_dict)

# ------------------------------------------- Filtering: MAIN : (END) --------------------------------------






# ------------------------------------------- Real-Time (Crontab) Variable Storing (START) -----------------------------
# Write and Save Variables For Real Time Updated
if real_time:
    store_variables = False
else:
    store_variables = True

if store_variables == True:
    with open('kalman_data.csv', 'w') as f:
        current_state_estimate, current_prob_estimate = kalman_filter.store_variables()
        f.write("%s, %s\n" % (current_state_estimate, current_prob_estimate))

# ------------------------------------------- Real-Time (Crontab) Variable Storing (END) -----------------------------




# ------------------------------------------- View Filtered Data On Graph (START) -----------------------------
# Plot Seaborn

"""
    Change Sea_Plot to True
"""
Sea_Plot = True
if Sea_Plot == True:
    df["Time/Date"] = pd.to_datetime(df["Time/Date"])
    start_date = '2021-01-01'
    end_date = '2021-03-30'
    start_index_loc = df[df['Time/Date'] == start_date].index
    end_index_loc = df[df['Time/Date'] == end_date].index

    level_data = level_data[start_index_loc[0]:end_index_loc[0]]
    level_data = level_data.reset_index()
    level_data = level_data["Level"]

    # Format Seaborn Data
    g = sns.lineplot(data=level_data, label = "Unfiltered Sensor Data").set_title(f"Sensor Data Between \n {start_date} & {end_date}")
    g = sns.lineplot(data=kalman_filter_estimates[start_index_loc[0]:end_index_loc[0]], label = "Filtered Data")
    g.set_xticklabels([start_date])
    ylabel('CS0 Water Level (%)')
    ylim([0,150])
    plt.legend()
    plt.show()
# ------------------------------------------- View Filtered Data On Graph (END) -----------------------------





use_matlib = False
if use_matlib:
    plt.plot(level_data)
    title("Filtering Real-Time Data")
    ylabel('CS0 Water Level (%)')
    xlabel('Dates')
    ylim([0,100])
    plt.plot(kalman_filter_estimates, 'k', linewidth=2.0)
    # Show the plot
    plt.show()





# ------------------------------------------- Create Filtered Data CSV (START)-----------------------------------------
create_csv = True
if create_csv:
    with open('16090_CSO_SLM_data_KF.csv', 'w') as f:
        for i, key in enumerate(kalman_filtered_data_dict.keys()):
            if i == 0:
                f.write("%s,%s,%s,%s\n" % (key, kalman_filtered_data_dict[key][0], kalman_filtered_data_dict[key][1], kalman_filtered_data_dict[key][2]))
            else:
                f.write("%s,%.2f,%.2f,%i\n"%(key, kalman_filtered_data_dict[key][0],kalman_filtered_data_dict[key][1], 1 if kalman_filtered_data_dict[key][0] > 100 else 0))
# ------------------------------------------- Create Filtered Data CSV (END)--------------------------------------------
