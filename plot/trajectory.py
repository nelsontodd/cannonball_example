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


def construct_trajectory_plots(arr, title):
  
  assert arr[0].columns[3] == ' v_y', 'Incorrect Columns.'
  fig, ax = plt.subplots(nrows = 2, ncols = 3, figsize=(12, 12))
  fig.subplots_adjust(left=0, bottom=0, right=1, top=1, wspace=0, hspace=0)
  time_deltas = [pow(10,-5), pow(10,-4), pow(10,-3), pow(10,-2), pow(10,-1), 1]
  count = 0
  i = 0
  for row in ax:
    j = 0
    for col in row:
      ax[i, j].plot(arr[count]['x'], arr[count][' y'])
      ax[i, j].spines['top'].set_visible(False)
      ax[i, j].spines['right'].set_visible(False)
      ax[i, j].spines['bottom'].set_visible(False)
      ax[i, j].spines['left'].set_visible(False)
      ax[i, j].title.set_text(str(time_deltas[count]))
      j+=1
      count+=1
    i+=1
  fig.suptitle('Trajectory for {} Model, Varying Time Deltas 10^-5 to 1'.format(title), fontsize=16)
  fig.text(0.5, 0.01, 'theta', ha='center', va='center', fontsize=16)
  fig.text(0.01, 0.5, 'dtheta', ha='center', va='center', rotation='vertical', fontsize=16)
  fig.tight_layout(rect=[0, 0.03, 1, 0.95])
  return fig, ax


def construct_trajectory_plot(df, title, time_delta):
  
  fig, ax = plt.subplots(figsize=(12, 12))
  fig.subplots_adjust(left=0, bottom=0, right=1, top=1, wspace=0, hspace=0)
  ax.plot(df['x'], df[' y'])
  ax.spines['top'].set_visible(False)
  ax.spines['right'].set_visible(False)
  ax.spines['bottom'].set_visible(False)
  ax.spines['left'].set_visible(False)
  fig.suptitle('Trajectory for {} Model Time Delta of {}'.format(title, time_delta), fontsize=16)
  fig.text(0.5, 0.01, 'theta', ha='center', va='center', fontsize=16)
  fig.text(0.01, 0.5, 'dtheta', ha='center', va='center', rotation='vertical', fontsize=16)
  fig.tight_layout(rect=[0, 0.03, 1, 0.95])
  return fig, ax


if __name__=="__main__":

  #Get the lists of all our files
	cnl_files = findfiles('output', r'cnl_[0-5]\.csv')
	cnl_files.sort(key=alphanum_key)
	cnl = list(map(lambda x: pd.read_csv(x), cnl_files))
	longdouble_files = findfiles('output', r'longdouble_[0-5]\.csv')
	longdouble_files.sort(key=alphanum_key)
	longdouble = list(map(lambda x: pd.read_csv(x), longdouble_files))
	double_files = findfiles('output', r'double_[0-5]\.csv')
	double_files.sort(key=alphanum_key)
	double = list(map(lambda x: pd.read_csv(x), double_files))
	float_files = findfiles('output', r'float_[0-5]\.csv')
	float_files.sort(key=alphanum_key)
	print(float_files)
	floats = list(map(lambda x: pd.read_csv(x), float_files))

	construct_trajectory_plots(cnl, 'CNL')
	plt.savefig('output/cnl_trajectory.png')
	construct_trajectory_plot(cnl[0], 'CNL', '10^-5')
	plt.savefig('output/cnl_trajectory_0.png')
	construct_trajectory_plots(longdouble, 'Long Double')
	plt.savefig('output/longdouble_trajectory.png')
	construct_trajectory_plots(double, 'Double')
	plt.savefig('output/double_trajectory.png')
	construct_trajectory_plots(floats, 'Float')
	plt.savefig('output/float_trajectory.png')
