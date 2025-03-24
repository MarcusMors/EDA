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
        bins = np.array(bins)

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
