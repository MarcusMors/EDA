import matplotlib.pyplot as plt
import numpy as np
from scipy.stats import norm  # For the Gaussian function


def main():
    dims = [10, 50, 100, 500, 1000, 2000, 5000]

    for d in dims:
        data = input()
        data = data.split(" ")

        if data[-1] == "":
            data.pop()

        data = list(map(float, data))

        # Compute mean (mu) and standard deviation (sigma)
        mu, std = norm.fit(data)

        fig, ax = plt.subplots()

        _, bins, _ = ax.hist(data, bins=25, alpha=1, color="b", rwidth=0.9)
        # plt.hist(data, bins=25, density=True, alpha=0.6, color='b')
        bins = np.array(bins)

        # p = norm.pdf(x, mu, std) * 4
        # p = norm.pdf(x, mu, std) * len(data)
        # print("------------------")
        # for i in range(len(data)*2//5,len(data)*3//5):
        #     print(f"{bins[i] - bins[i-1]=}")
        # print("------------------")
        # p = norm.pdf(x, mu, std) * (bins[1] - bins[0]) * 25000
        # p = norm.pdf(x, mu, std) * (bins[1] - bins[0]) * 50000
        print(len(data))
        ax.set_xlim(0, None)
        ax.set_xlabel(f"Distance in a {d}-dimensional sphere")
        ax.set_title(f"Histogram for {d} Dimensions")

        ax.legend()
        fig.tight_layout()
        plt.savefig(f"RAD_histogram_{d}.png")
        plt.close(fig)


if __name__ == "__main__":
    main()
