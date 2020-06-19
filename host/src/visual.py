from matplotlib import pyplot as plt
import pandas as pd
df = pd.read_csv("neuron_data.csv")

df.T.plot()
plt.savefig('fig.png')