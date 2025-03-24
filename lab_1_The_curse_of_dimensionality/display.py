import matplotlib.pyplot as plt
import numpy as np
from scipy.stats import norm  # For the Gaussian function


def main():
    dims = [10, 50, 100, 500, 1000, 2000, 5000]
    mus = []
    for d in dims:
        data = input()
        data = data.split(" ")

        if data[-1] == "":
            data.pop()

        data = list(map(float, data))

        # Compute mean (mu) and standard deviation (sigma)
        mu, std = norm.fit(data)
        mus.append(mu)
        fig, ax = plt.subplots()

        _, bins, _ = ax.hist(
            data, bins=10, density=True, alpha=1, color="b", rwidth=0.9
        )
        # plt.hist(data, bins=25, density=True, alpha=0.6, color='b')
        bins = np.array(bins)

        xmin, xmax = plt.xlim()
        x = np.linspace(xmin, xmax, 100)
        # p = norm.pdf(x, mu, std) * 4
        # p = norm.pdf(x, mu, std) * len(data)
        # print("------------------")
        # for i in range(len(data)*2//5,len(data)*3//5):
        #     print(f"{bins[i] - bins[i-1]=}")
        # print("------------------")
        p = norm.pdf(x, mu, std) * (bins[1] - bins[0]) * 350
        # p = norm.pdf(x, mu, std) * (bins[1] - bins[0]) * 25000
        # p = norm.pdf(x, mu, std) * (bins[1] - bins[0]) * 50000
        print(len(data))
        ax.plot(x, p, "-.", linewidth=1, color="red")
        ax.set_xlim(0, None)

        ax.set_xlabel("Distance")
        ax.set_ylabel("Probability Density")
        ax.set_title(f"Gaussian Fit for {d} Dimensions")

        ax.legend()
        fig.tight_layout()
        plt.savefig(f"gaussian_fit_{d}.png")
        plt.close(fig)

    fig, ax = plt.subplots()
    ax.plot(dims, mus, "-o", color="b")
    ax.set_xlabel("Number of Dimensions")
    ax.set_ylabel("Mean")
    ax.set_title("Mean vs. Number of Dimensions")
    plt.savefig("mean_vs_dimensions.png")


if __name__ == "__main__":
    main()
