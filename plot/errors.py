import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import os
import re
import matplotlib as mpl
import re
mpl.rcParams['agg.path.chunksize'] = 10000


def tryint(s):
	try:
		return int(s)
	except ValueError:
		return s
     
def alphanum_key(s):
	""" Turn a string into a list of string and number chunks.
	"z23a" -> ["z", 23, "a"]
	"""
	return [ tryint(c) for c in re.split('([0-9]+)', s) ]

def findfiles(path, regex):
	regObj = re.compile(regex)
	res = []
	for root, dirs, fnames in os.walk(path):
		for fname in fnames:
			if regObj.match(fname):
				res.append(os.path.join(root, fname))
	return res



def construct_trajectory_error_plots(arr, title):
  
  assert arr[0].columns[3] == ' v_y', 'Incorrect Columns.'
  fig, ax = plt.subplots(nrows = 2, ncols = 3)
  count = 0
  i = 0
  df = pd.DataFrame()
  for row in ax:
    j = 0
    for col in row:
      df['x'] = longdouble[count]['x']
      df['y'] = ((longdouble[count][' y'] - arr[count][' y']))
      df.drop(df.tail(10).index,inplace=True)
      df.dropna(inplace=True)
      print(df)
      ax[i, j].plot(df['x'], df['y'])
      ax[i, j].spines['top'].set_visible(False)
      ax[i, j].spines['right'].set_visible(False)
      ax[i, j].spines['bottom'].set_visible(False)
      ax[i, j].spines['left'].set_visible(False)
      j+=1
      count+=1
    i+=1
  fig.suptitle('Error for {} Model, Varying Time Delta from 10^-5 to 1'.format(title), fontsize=16)
  fig.text(0.5, 0.04, 'x', ha='center', va='center')
  fig.text(-0.1, 0.5, 'y', ha='center', va='center', rotation='vertical')
  return fig, ax

def construct_final_pos_error_plots(arr, title):
  
  assert arr[0].columns[3] == ' v_y', 'Incorrect Columns.'
  errors = [longdouble[x]['x'].iloc[-1] - arr[x]['x'].iloc[-1] for x in range(len(arr))]
  fig, ax = plt.subplots(figsize=(12,12))
  x = [str(pow(10,x)) for x in range(-5, 1)]
  ax.bar(x, errors)
  ax.spines['top'].set_visible(False)
  ax.spines['right'].set_visible(False)
  ax.spines['bottom'].set_visible(False)
  ax.spines['left'].set_visible(False)
  for tick in ax.xaxis.get_major_ticks():
    tick.label.set_fontsize(14)
  for tick in ax.yaxis.get_major_ticks():
    tick.label.set_fontsize(14)
  fig.suptitle('Error for {} Model, Varying Time Delta from 10^-5 to 1'.format(title), fontsize=20)
  fig.text(0.5, 0.01, 'Difference in Final Landing Position (Meters)', ha='center', va='center', fontsize=16)
  fig.text(0.01, 0.5, 'Time Step (Seconds)', ha='center', va='center', rotation='vertical', fontsize=16)
  fig.tight_layout(rect=[0, 0.03, 1, 0.95])
  return fig, ax


def construct_final_pos_superimposed_plots(arr, title):
  
  assert arr[0].columns[3] == ' v_y', 'Incorrect Columns.'
  errors = [longdouble[x]['x'].iloc[-1] - arr[x]['x'].iloc[-1] for x in range(len(arr))]
  fig, ax = plt.subplots(figsize=(12,12))
  width = 0.35
  xlabels = [str(pow(10,x)) for x in range(-5, 1)]
  x = np.arange(len(xlabels))
  ax.bar(x - width/2, [longdouble[x]['x'].iloc[-1] for x in range(len(arr))], width, label='Long Double')
  ax.bar(x + width/2, [arr[x]['x'].iloc[-1] for x in range(len(arr))], width, label='{}'.format(title))
  ax.spines['top'].set_visible(False)
  ax.spines['right'].set_visible(False)
  ax.spines['bottom'].set_visible(False)
  ax.spines['left'].set_visible(False)
  ax.set_yticklabels(xlabels)
  ax.legend()
  for tick in ax.xaxis.get_major_ticks():
    tick.label.set_fontsize(14)
  for tick in ax.yaxis.get_major_ticks():
    tick.label.set_fontsize(14)
  fig.suptitle('Landing Position for {} Model, Varying Time Delta from 10^-5 to 1'.format(title), fontsize=20)
  fig.text(0.5, 0.01, 'Final Landing Position (Meters)', ha='center', va='center', fontsize=16)
  fig.text(0.01, 0.5, 'Time Step (Seconds)', ha='center', va='center', rotation='vertical', fontsize=16)
  fig.tight_layout(rect=[0, 0.03, 1, 0.95])
  return fig, ax


def construct_final_pos_superimposed_error_plots(arr, arr2, typename1, typename2):
  
  assert arr[0].columns[3] == ' v_y', 'Incorrect Columns.'
  errors = [longdouble[x]['x'].iloc[-1] - arr[x]['x'].iloc[-1] for x in range(len(arr))]
  errors2 = [longdouble[x]['x'].iloc[-1] - arr2[x]['x'].iloc[-1] for x in range(len(arr2))]
  fig, ax = plt.subplots(figsize=(12,12))
  width = 0.35
  xlabels = [str(pow(10,x)) for x in range(-6, 1)]
  x = np.arange(len(xlabels) - 1)
  print(x)
  ax.bar(x - width/2, errors, width, label='{}'.format(typename1))
  ax.bar(x + width/2, errors2, width, label='{}'.format(typename2))
  ax.spines['top'].set_visible(False)
  ax.spines['right'].set_visible(False)
  ax.spines['bottom'].set_visible(False)
  ax.spines['left'].set_visible(False)
  ax.set_xticklabels(xlabels)
  ax.legend(prop={'size':24})
  for tick in ax.xaxis.get_major_ticks():
    tick.label.set_fontsize(14)
  for tick in ax.yaxis.get_major_ticks():
    tick.label.set_fontsize(14)
  fig.suptitle('Landing Position Error vs Long Double Simulation, Varying Time Delta', fontsize=24)
  fig.text(0.5, 0.01,'Time Step (Seconds)', ha='center', va='center', fontsize=20)
  fig.text(0.02, 0.5, 'Difference in Landing Position vs Long Double (Meters)', ha='center', va='center', rotation='vertical', fontsize=20)
  fig.tight_layout(rect=[0.05, 0.03, 1, 0.95])
  fig.gca().invert_yaxis()
  return fig, ax


global longdouble_files
global longdouble

if __name__=="__main__":

  #Get the lists of all our files
  longdouble_files = findfiles('output', r'longdouble_[0-5]\.csv')
  longdouble_files.sort(key=alphanum_key)
  longdouble = list(map(lambda x: pd.read_csv(x), longdouble_files))
  cnl_files = findfiles('output', r'cnl_[0-5]\.csv')
  cnl_files.sort(key=alphanum_key)
  cnl = list(map(lambda x: pd.read_csv(x), cnl_files))
  double_files = findfiles('output', r'double_[0-5]\.csv')
  double_files.sort(key=alphanum_key)
  double = list(map(lambda x: pd.read_csv(x), double_files))
  float_files = findfiles('output', r'float_[0-5]\.csv')
  float_files.sort(key=alphanum_key)
  print(float_files)
  floats = list(map(lambda x: pd.read_csv(x), float_files))

  #construct_trajectory_error_plots(cnl, 'cnl')
  #plt.savefig('output/cnl_trajectory_error.png')
  #construct_trajectory_error_plots(double, 'double')
  #plt.savefig('output/double_trajectory_error.png')
  #construct_trajectory_error_plots(floats, 'float')
  #plt.savefig('output/float_trajectory_error.png')

  construct_final_pos_error_plots(cnl, 'CNL')
  plt.savefig('output/cnl_final_pos_error.png')
  construct_final_pos_error_plots(double, 'Double')
  plt.savefig('output/double_final_pos_error.png')
  construct_final_pos_error_plots(floats, 'Float')
  plt.savefig('output/float_final_pos_error.png')
  construct_final_pos_superimposed_plots(cnl, 'CNL')
  plt.savefig('output/superimposed_final_pos_cnl_vs_longdouble.png')
  construct_final_pos_superimposed_error_plots(cnl, floats, 'CNL', 'Float')
  plt.savefig('output/superimposed_final_pos_error.png')
