import os

neural_src = os.getenv('NEURAL_SRC')
os.chdir(neural_src)
import mnist_loader