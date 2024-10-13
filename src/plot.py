# import matplotlib.pyplot as plt
# import pandas as pd

# out = pd.read_csv("out.csv", sep=",")
# out.plot(x="vol", y="press")

# plt.title("Clapeyron")
# plt.show()


import matplotlib.pyplot as plt
import pandas as pd

out = pd.read_csv("out.csv", sep=",")
while True:
    out.plot(x="vol", y="press")
    plt.show()
