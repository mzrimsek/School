import os
import sys

neural_src = os.getenv('NEURAL_SRC')
sys.path.append(neural_src);
os.chdir(neural_src)
import mnist_loader