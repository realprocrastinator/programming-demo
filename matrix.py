#=============================================================================
#Matrix Operation
#normalise matrix row wise
x=[[0,3,4],
   [2,4,6]]
#axis 1 is row 0 is column, keepdims =true means compute norm row wise or column wise
∥x∥=np.linalg.norm(x,axis=1,keepdims=True)=[556⎯⎯⎯⎯√](4)

#if x1 and x2 are the 1 d array will dot the dot product, but if x1 and x2 are the matrix will
#do the matrix multiplication
dot = np.dot(x1,x2)
sum = x1*x2 #will multiply element wise and can use braodcasting

#Broad casting
np.exp(x) #apply exp() element wise to x
np.sum(x, axis = 1, keepdims = True) #sum each row of x matrix

#np.maximum compare array or matrix element wise and get the maximum from the comp
>>> np.maximum([2, 3, 4], [1, 5, 2])
array([2, 5, 4])
>>> np.maximum(np.eye(2), [0.5, 2]) # broadcasting
array([[ 1. ,  2. ],
       [ 0.5,  2. ]])

#Matrix Multiplication
np.matmul(a, c)

#init zero matrix
np.zeros((2, 1))

#elementwise multiplication
matrix1 * matrix2
np.multiply(matrix1,matrix2)


#============================================================================
#reshape
#A trick when you want to flatten a matrix X of shape (a,b,c,d) to a matrix X_flatten of shape (b ∗∗ c ∗∗ d, a) is to use:
#One shape dimension can be -1. In this case, the value is inferred from the length of the array and remaining dimensions
X_flatten = X.reshape(X.shape[0], -1).T      # X.T is the transpose of X
cost = np.squeeze(cost)      # To make sure your cost's shape is what we expect (e.g. this turns [[17]] into 17).
#transform a 1 D row vector to a column vector
print(features)
> array([ 0.49671415, -0.1382643 ,  0.64768854])
print(features[:, None])
> array([[ 0.49671415],
       [-0.1382643 ],
       [ 0.64768854]])

#or create 2D vector and transpose directly
np.array(features, ndmin=2)
> array([[ 0.49671415, -0.1382643 ,  0.64768854]])

np.array(features, ndmin=2).T
> array([[ 0.49671415],
       [-0.1382643 ],
       [ 0.64768854]])

#============================================================================
#random & initialisation
np.zeros_like(A) #return a zero matrix of the same size of the input matrix
np.zeros((3,4))
np.zeros(3)
np.random.rand(3,2) #random matrix random number from normal distribution of [0.1]

#pick item according to the prob distribution
#https://docs.scipy.org/doc/numpy-1.13.0/reference/generated/numpy.random.choice.html
#a:1-D array-like or int
#size:Output shape
#replace:whether the sample is with or without replacment
#p : 1-D array-like, optional ,the porbability distribution associated with the array
numpy.random.choice(a, size=None, replace=True, p=None)¶


#============================================================================
#create a mesh grid return a matrix of x coordinates and y coordinates
x,y = np.meshgrid(np.arange(0, xsize), np.arange(0, ysize))

#given two points will return the parametre of the line that fit the two points
#return [a,b] #y = ax + b
np.polyfit((x1,y1),(x2,y2),1)

#Fills the area bounded by one or more polygons by the specified color
#img – Image.
#pts – Array of polygons where each polygon is represented as an array of points.
#npts – Array of polygon vertex counters.
#ncontours – Number of contours that bind the filled region.
#color – Polygon color.
#lineType – Type of the polygon boundaries. See the line() description.
#shift – Number of fractional bits in the vertex coordinates.
#offset – Optional offset of all points of the contours.
cv2.fillPoly(img, pts, color[, lineType[, shift[, offset]]]) 

#============================================================================
#logic operator 
~a , bitwise negation 
cv2.bitwise_and(src1, src2[, dst[, mask]]) 

#============================================================================
#Stack Matrix
#vstack concatenates along the first dimension stack matrix vertically
print(a.shape, b.shape)
# (3, 2) (3, 2)
print(np.vstack((a, b)).shape)
# (6, 2)

#hstack concatenates along the second dimension stack matrix horizontally
print(np.hstack((a, b)).shape)
# (3, 4)

#np.dstack concatenates along the third dimension.
print(np.dstack((a, b)).shape)
# (3, 2, 2)
numpy.dstack(tup)
e.g.
>>> a = np.array((1,2,3))
>>> b = np.array((2,3,4))
>>> np.dstack((a,b))
array([[[1, 2],
        [2, 3],
        [3, 4]]])

#Matrix transpose
np.transpose(a,(2,1,0)) #(matrix,(axis1,axis2,axis3)) axies is the axies order
#======================================================
#clipping
#https://docs.scipy.org/doc/numpy-1.13.0/reference/generated/numpy.clip.html
#a:Array containing elements to clip.
#out:save the result of clipping has to have same dim as a
numpy.clip(a, a_min, a_max, out=None)

#==============================================================================
#Meticulous
#nonzero(matrix) retrun a array of index of none zero entry in the matrix in the order 
#of x ,y and z
x = np.array([[1,0,0], [0,2,0], [1,1,0]])x = np.array([[1,0,0], [0,2,0], [1,1,0]])
>>> x
array([[1, 0, 0],
       [0, 2, 0],
       [1, 1, 0]])``
>>> np.nonzero(x)
(array([0, 1, 2, 2]), array([0, 1, 0, 1]))





#return numbers of evenly sapced 
#retstep: If True, return (samples, step), where step is the spacing between samples.
#dtype : dtype, optional:The type of the output array. If dtype is not given, infer the data type from the other input arguments.
numpy.linspace(start, stop, num=50, endpoint=True, retstep=False, dtype=None)
>>> np.linspace(2.0, 3.0, num=5)
array([ 2.  ,  2.25,  2.5 ,  2.75,  3.  ])
>>> np.linspace(2.0, 3.0, num=5, endpoint=False)
array([ 2. ,  2.2,  2.4,  2.6,  2.8])
>>> np.linspace(2.0, 3.0, num=5, retstep=True)
(array([ 2.  ,  2.25,  2.5 ,  2.75,  3.  ]), 0.25)

np.linspace(0, binary_warped.shape[0]-1, binary_warped.shape[0] )


#Returns the indices of the maximum values along an axis.
# out: If provided, the result will be inserted into this array. It should be of the appropriate shape and dtype.
#axis is by default the index of the flatened array
numpy.argmax(a, axis=None, out=None)[source]

#==============================================================================
#Open CV

#Canny Edge detection: gradieant greater than high will be detected and below low will
#be throw away , anything in between will only be included if it is connected to a pixel that is 
#higher than the high
#will return a binary image of black and white
#the ration low/high = 1:2 or 1:3
#internally Canny will apply Guassian soomthing to remove noise
edges = cv2.Canny(gray, low_threshold, high_threshold)


#Houghs Lines
#return array of segment of lines detected [(x1, y1, x2, y2),...]
#rho and theta are the distance and angular resolution of our grid in Hough space.
#You need to specify rho in units of pixels and theta in units of radians.
#The threshold parameter specifies the minimum number of votes (intersections in a given grid cell) a candidate line needs to have to make it into the output.
#The empty np.array([]) is just a placeholder, no need to change it. 
#min_line_length is the minimum length of a line (in pixels) that you will accept in the output
#max_line_gap is the maximum distance (again, in pixels) between segments that you will allow to be connected into a single line. 
lines = cv2.HoughLinesP(masked_edges, rho, theta, threshold, np.array([]),min_line_length, max_line_gap)

#Draw a line
cv2.line(img,(x1,y1),(x2,y2),(255,0,0),int thinkness, int type, int shift)


#fillpoly Fills the area bounded by one or more polygons.
#pts – Array of polygons where each polygon is represented as an array of points.
#color – Polygon color.
cv2.fillPoly(img, pts, color[, lineType[, shift[, offset]]]) → None
cv2.fillPoly(color_warp, np.int_([pts]), (0,255, 0))




#combine two images
combo = cv2.addWeighted(first_input_array,double weight1, second_input_array,double weight2, double scalar_added)

#chess board Camera calabritation
#ret, corners = cv2.findChessboardCorners(gray, (nx, ny), None)
#cv2.drawChessboardCorners(img, (nx, ny), corners, ret)
cv2.findChessboardCorners(image, patternSize[, corners[, flags]]) → retval, corners
cv2.drawChessboardCorners(image, patternSize, corners, patternWasFound) → None¶

#np.mgrid will mesh grid as specified
>>> np.mgrid[0:3,1:4]
array([[[0, 0, 0],
        [1, 1, 1],
        [2, 2, 2]],

       [[1, 2, 3],
        [1, 2, 3],
        [1, 2, 3]]])
>>> np.mgrid[0:3,1:4].shape
(2, 3, 3)


#Camera Calibration
#gray.shape[::-1] will return the with and hight of the image
#or using the the first two value of the original image img.shape[1::-1]
ret, mtx, dist, rvecs, tvecs = cv2.calibrateCamera(objpoints, imgpoints, gray.shape[::-1], None, None)
#Undistort a image
dst = cv2.undistort(img, mtx, dist, None, mtx)

#set to gray scale
gray = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY) #cv2.imread()
gray = cv2.cvtColor(img,cv2.COLOR_RGB2GRAY) #img = mpimg.imread()

#perspective transform
#src and dst could be the four point of the original image that mapped to the 
#location that you want on the new image , since 4 points are sufficient to define a linear transformation
M = cv2.getPerspectiveTransform(src, dst) #will retrun a transformation matrix
Minv = cv2.getPerspectiveTransform(dst, src) #the inverse transformation matrix
warped = cv2.warpPerspective(img, M, img_size, flags=cv2.INTER_LINEAR) #transform the image to the desired one


#sobel Gradient
sobelx = cv2.Sobel(gray, cv2.CV_64F, 1, 0,kernel_size = 3) #1 and 0 indicating taking derivative in the x dir
sobely = cv2.Sobel(gray, cv2.CV_64F, 0, 1,kernel_size = 3)
abs_sobelx = np.absolute(sobelx)
scaled_sobel = np.uint8(255*abs_sobelx/np.max(abs_sobelx)) #Convert the absolute value image to 8-bit:
#apply a threshould to the gradient to show the binary image accordingly
thresh_min = 20
thresh_max = 100
sxbinary = np.zeros_like(scaled_sobel)
sxbinary[(scaled_sobel >= thresh_min) & (scaled_sobel <= thresh_max)] = 1
plt.imshow(sxbinary, cmap='gray')

#color spacing
hls = cv2.cvtColor(image, cv2.COLOR_RGB2HLS) #transfer from RGB color spaace to HLS

#color trackbar
#https://docs.opencv.org/3.0-beta/doc/py_tutorials/py_gui/py_trackbar/py_trackbar.html
#==============================================================================
#subplot
#https://matplotlib.org/api/_as_gen/matplotlib.pyplot.subplot.html
subplot(nrows, ncols, index, **kwargs)
subplot(pos, **kwargs)
subplot(ax)
plt.subplot(221)

# equivalent but more general
ax1=plt.subplot(2, 2, 1)


#==============================================================================
#tensor flow
#init a 3 by 1 constant
X = tf.constant(np.random.randn(3,1), name = "X")
x = tf.placeholder(tf.int64, ,shape = (3,2),name = 'x') #init a place holder
x = tf.Variable(5)
sess.run(2 * x, feed_dict = {x: 3}) #later can be evaluted by the value given usinng feed_dict = {x:3}
init = tf.global_variables_initializer()  #init all the variable defined
sess = tf.Session() #define a session
c = tf.multiply(a,b)
print(sess.run(c)) #run a session and evaluate the result


#get existing variable
W1 = tf.get_variable("W1",[4,4,3,8],initializer = tf.contrib.layers.xavier_initializer(seed = 0))
                

#to randam initialise according to the normal distribution whoes value is no more than
#2 standard deviation from the mean
tf.truncated_normal((n_features, n_labels))

#cast one data type to anther
tf.cast(tf.constant(1), tf.float64))

#tf arithmetic
tf.add(a,b)
tf.mul(a,b)
tf.matmul(a,b)
tf.transpose()
#hot encoding
#covert lable vector of y 1 by n to columns of the corresponding row of 1
tf.one_hot(labels, depth, axis) #deepths along which axies

#compute the cost function
tf.nn.sigmoid_cross_entropy_with_logits(logists=, labels= )
#the soft_max_cross need logits and lable of shape (examples,number_of_classes)
tf.reduce_mean(tf.nn.softmax_cross_entropy_with_logits(logits = ..., labels = ...))

#init ones or zeros
tf.ones(shape)
tf.zeros(shape)
W1 = tf.get_variable("W1", [25,12288], initializer = tf.contrib.layers.xavier_initializer(seed = 1))
b1 = tf.get_variable("b1", [25,1], initializer = tf.zeros_initializer())

#NN functions
tf.nn.relu(...)


#gradient decent optimizer
optimizer = tf.train.GradientDescentOptimizer(learning_rate = learning_rate).minimize(cost)
_ , c = sess.run([optimizer, cost], feed_dict={X: minibatch_X, Y: minibatch_Y})


# Class used to save and/or restore Tensor Variables
saver = tf.train.Saver()
saver.save(sess, "file_to_save")

#load back a previously saved model
# Remove the previous weights and bias
tf.reset_default_graph()
# Load the weights and bias
#Since tf.train.Saver.restore() sets all the TensorFlow Variables, you don't need to call tf.global_variables_initializer().
#it will restore all the previously saved variables

saver.restore(sess, save_file)
#when tf try to load the variables it will load variable with the matching name , if 
#no name was assigned to the variable when assigned ,it will assign the nanme type_number and would
#potentially confused when load back the stored variable ,due to mis match of the name
weights = tf.Variable(tf.truncated_normal([2, 3]), name='weights_0')


#return the index of the max value of that axies, axis = 0 compare rows, axis = 1 compare columns
tf.argmax(input, axis=None, name=None, dimension=None)

#drop out function
#n order to compensate for dropped units, tf.nn.dropout() multiplies all units that are kept (i.e. not dropped) by 1/keep_prob
tf.dropout(hidden_layer,keep_prob)




#np.pad
>>> a = [1, 2, 3, 4, 5]
>>> np.pad(a, (2,3), 'constant', constant_values=(4, 6))
array([4, 4, 1, 2, 3, 4, 5, 6, 6, 6])


#convolution network
#stride is the stride for each dimention of the input
tf.nn.conv2d(X,W1, strides = [1,s,s,1], padding = 'SAME')

#tf.nn.max_pool(A, ksize = [1,f,f,1], strides = [1,s,s,1], padding = 'SAME'): given an input A, 
#this function uses a window of size (f, f) and strides of size (s, s) 
#to carry out max pooling over each window. 
tf.nn.max_pool(A, ksize = [1,f,f,1], strides = [1,s,s,1], padding = 'SAME'): 
tf.nn.relu(Z1) # computes the elementwise ReLU of Z1 (which can be any shape). 
# given an input P, this function flattens 
#each example into a 1D vector it while maintaining the batch-size. 
#It returns a flattened tensor with shape [batch_size, k]. You can read the full documentation
tf.contrib.layers.flatten(P) 
# given a the flattened input F, it returns the output computed using a fully connected layer
#num_outputs: Integer or long, the number of output units in the layer.
#given a the flattened input F, it returns the output computed using a fully connected layer.
#the fully connected layer automatically initializes weights in the graph 
#and keeps on training them as you train the model. Hence, you did not need 
#to initialize those weights when initializing the parameters
tf.contrib.layers.fully_connected(F, num_outputs,activation_fn=None)
#given an input P, this function flattens each example into a 1D vector 
#it while maintaining the batch-size. It returns a flattened tensor with shape [batch_size, k].
tf.contrib.layers.flatten(P) 

#comput the softmax cross entropy cost
# computes the softmax entropy loss. This function both computes the 
#softmax activation function as well as the resulting loss
#return the same dimetion as labels
tf.nn.softmax_cross_entropy_with_logits(logits = Z3, labels = Y)


#resize batches of images 
#images could be 4d of (m, h, w, c) or 3d(h,w,c) will return 4d or 3d accordingly
#reszied images
tf.image.resize_images(
    images,
    size,
    method=ResizeMethod.BILINEAR,
    align_corners=False,
    preserve_aspect_ratio=False
)


#============================================================================
#Keras
#Dense implements the operation: output = activation(dot(input, kernel) + bias)
#units: Positive integer, dimensionality of the output space.
keras.layers.Dense(units, activation=None, use_bias=True, kernel_initializer='glorot_uniform', bias_initializer='zeros', kernel_regularizer=None, bias_regularizer=None, activity_regularizer=None, kernel_constraint=None, bias_constraint=None)
#create a fully connected layer
X = Flatten()(X)
X = Dense(1, activation='sigmoid', name='fc')(X)


#will create Keras instance 
model = Model(inputs = X_input, outputs = X, name='HappyModel')

#dim in BatchNormalization
#for other np multi dim array then specify an axis we mean to collape that axix while
#keeping all the other axies the same
#When we compute a BatchNormalization along an axis, we preserve the dimensions of the array, 
#and we normalize with respect to the mean and standard deviation over every other axis
#meaning carry out normalisation within separate channels
X = BatchNormalization(axis = 3, name = bn_name_base + '2a')(X)

#Udacity
from keras.models import Sequential

# Create the Sequential model
model = Sequential()
model.add(Flatten(input_shape=(32, 32, 3)))
model.add(Dense(100))
model.add(Activation('relu'))
model.add(Conv2D(32,kernel_size = (3,3),activation = 'relu',input_shape = input_shape))
model.add(MaxPooling2D(pool_size=(2, 2)))
model.add(Dropout(0.25))
#complie the model specify how to train the model
compile(optimizer, loss=None, metrics=None, loss_weights=None, sample_weight_mode=None, weighted_metrics=None, target_tensors=None)
#e.g.
model.compile('adam', 'categorical_crossentropy', ['accuracy'])


#batch_size was set to 32 by default
model.evaluate(x=None, y=None, batch_size=None, verbose=1, sample_weight=None, steps=None, callbacks=None)


#keras pre trained modles
https://keras.io/applications/

#include_top is for whether you want to include the fully-connected layer at the top of the network; unless you are actually trying to classify ImageNet's 1,000 classes, you likely want to set this to False and add your own additional layer for the output you desire.
from keras.applications.vgg16 import VGG16
from keras.preprocessing import image
from keras.applications.vgg16 import preprocess_input
import numpy as np

#VGG16
model = VGG16(weights='imagenet', include_top=False)
#preprocess the image as when training
img_path = 'your_image.jpg'
img = image.load_img(img_path, target_size=(224, 224)) #resize the image 
x = image.img_to_array(img) #image to array
x = np.expand_dims(x, axis=0) #expand the first dim as (1,h,w,c)
x = preprocess_input(x)  #precprocess the image
#make prediction
predictions = model.predict(x)
print('Predicted:', decode_predictions(predictions, top=3)[0])


#GoogleNet
import keras.applications.inception_v3 import InceptionV3
model = InceptionV3(weights='imagenet', include_top=False)

#ResNet
from keras.applications.resnet50 import ResNet50
model = ResNet50(weights='imagenet', include_top=False)

#implement the transfer learning
#to freeze the layers iterate through all the layers and set layer.trainable = False
for layer in model.layers:
    layer.trainable = False

#check NN architect
model.summary()
model.layer.pop() #would drop layers from the end toward the front

#Sequencial vs Model API:instead of model.add() will tell whick previous layer to attach to the curr layer
#e.g.
x = Dropout(0.2)(inp) #inp is the previous layer

#Transfer learning use Inception Net
#+++++++++++++++++++++++++++++++++++++++
from keras.layers import Input, Lambda
import tensorflow as tf
# Makes the input placeholder layer 32x32x3 for CIFAR-10
cifar_input = Input(shape=(32,32,3))
# Re-sizes the input with Kera's Lambda layer & attach to cifar_input
resized_input = Lambda(lambda image: tf.image.resize_images(
    image, (input_size, input_size)))(cifar_input)
# Feeds the re-sized input into Inception model
# You will need to update the model name if you changed it earlier!
inp = inception(resized_input)


# Imports fully-connected "Dense" layers & Global Average Pooling
from keras.layers import Dense, GlobalAveragePooling2D
x = GlobalAveragePooling2D()(inp) #add GlobalaveragePoool After the truncated inception model
x = Dense(512, activation = 'relu')(x) #add the fullly connected
predictions = Dense(10, activation = 'softmax')(x) #last softmax

from keras.models import Model
# Creates the model, assuming your final layer is named "predictions"
model = Model(inputs=cifar_input, outputs=predictions)
model.compile(optimizer='Adam', loss='categorical_crossentropy', metrics=['accuracy'])
model.summary()

#train the model
from sklearn.utils import shuffle
from sklearn.preprocessing import LabelBinarizer
from keras.datasets import cifar10
(X_train, y_train), (X_val, y_val) = cifar10.load_data()
# One-hot encode the labels
label_binarizer = LabelBinarizer()
y_one_hot_train = label_binarizer.fit_transform(y_train)
y_one_hot_val = label_binarizer.fit_transform(y_val)
# Shuffle the training & test data
X_train, y_one_hot_train = shuffle(X_train, y_one_hot_train)
X_val, y_one_hot_val = shuffle(X_val, y_one_hot_val)
# We are only going to use the first 10,000 images for speed reasons
# And only the first 2,000 images from the test set
X_train = X_train[:10000]
y_one_hot_train = y_one_hot_train[:10000]
X_val = X_val[:2000]
y_one_hot_val = y_one_hot_val[:2000]

# Use a generator to pre-process our images for ImageNet
from keras.preprocessing.image import ImageDataGenerator
from keras.applications.inception_v3 import preprocess_input
#Imgage Genrator will produce augmented images for the training set
if preprocess_flag == True:
    '''
    aug = ImageDataGenerator(rotation_range=20, zoom_range=0.15,
	width_shift_range=0.2, height_shift_range=0.2, shear_range=0.15,
	horizontal_flip=True, fill_mode="nearest")
    '''
    datagen = ImageDataGenerator(preprocessing_function=preprocess_input)
    val_datagen = ImageDataGenerator(preprocessing_function=preprocess_input)
else:
    datagen = ImageDataGenerator()
    val_datagen = ImageDataGenerator()

# Train the model
batch_size = 32
epochs = 5
# Note: we aren't using callbacks here since we only are using 5 epochs to conserve GPU time
#fit_generator() will generate the augemented data as per datafen function defined and generate a batch of the 
#batch_size each time and when it hits the steps_per_epoch it will know one epoch iteration have been reached.
model.fit_generator(datagen.flow(X_train, y_one_hot_train, batch_size=batch_size), 
                    steps_per_epoch=len(X_train)/batch_size, epochs=epochs, verbose=1, 
                    validation_data=val_datagen.flow(X_val, y_one_hot_val, batch_size=batch_size),
                    validation_steps=len(X_val)/batch_size)

#model.fit() vs model.fit_generator()
https://www.pyimagesearch.com/2018/12/24/how-to-use-keras-fit-and-fit_generator-a-hands-on-tutorial/

#+++++++++++++++++++++++++++++++++++++++
#keras Call Back
#This would save a model to a specified save_path, based on validation loss, and only save down the best models. 
#If you set save_best_only to False, every single epoch will save down another version of the model.
checkpoint = ModelCheckpoint(filepath=save_path, monitor='val_loss', save_best_only=True)
#This will monitor validation accuracy, and if it has not decreased by more than 0.0003 
#from the previous best validation accuracy for 5 epochs, training will end early.
stopper = EarlyStopping(monitor='val_acc', min_delta=0.0003, patience=5)
model.fit(callbacks=[checkpoint, stopper]) #specify the callback when fit the model

#+++++++++++++++++++++++++++++++++++++++
#Behavior cloning
#keras lambda layer
https://keras.io/layers/core/#lambda
keras.layers.Lambda(function, output_shape=None, mask=None, arguments=None)
#e.g.
from keras.models import Sequential, Model
from keras.layers import Lambda
# set up lambda layer
model = Sequential()
model.add(Lambda(lambda x: (x / 255.0) - 0.5, input_shape=(160,320,3)))
...

#self driving data augmentation
import numpy as np
image_flipped = np.fliplr(image)
measurement_flipped = -measurement

#cv flip
https://docs.opencv.org/2.4/modules/core/doc/operations_on_arrays.html#flip


#how to use 3 cameras in the front for training
with open(csv_file, 'r') as f:
    reader = csv.reader(f)
    for row in reader:
        steering_center = float(row[3])

        # create adjusted steering measurements for the side camera images
        correction = 0.2 # this is a parameter to tune
        steering_left = steering_center + correction
        steering_right = steering_center - correction

        # read in images from center, left and right cameras
        path = "..." # fill in the path to your training IMG directory
        img_center = process_image(np.asarray(Image.open(path + row[0])))
        img_left = process_image(np.asarray(Image.open(path + row[1])))
        img_right = process_image(np.asarray(Image.open(path + row[2])))

        # add images and angles to data set
        car_images.extend(img_center, img_left, img_right)
        steering_angles.extend(steering_center, steering_left, steering_right)

#crop images to leave only the lane info in the image
https://keras.io/layers/convolutional/#cropping2d
#e.g.
from keras.models import Sequential, Model
from keras.layers import Cropping2D
import cv2

# set up cropping2D layer
model = Sequential()
model.add(Cropping2D(cropping=((50,20), (0,0)), input_shape=(3,160,320)))
...


#history to visualise the loss
from keras.models import Model
import matplotlib.pyplot as plt

history_object = model.fit_generator(train_generator, samples_per_epoch =
    len(train_samples), validation_data =
    validation_generator,
    nb_val_samples = len(validation_samples),
    nb_epoch=5, verbose=1)

### print the keys contained in the history object
print(history_object.history.keys())

### plot the training and validation loss for each epoch
plt.plot(history_object.history['loss'])
plt.plot(history_object.history['val_loss'])
plt.title('model mean squared error loss')
plt.ylabel('mean squared error loss')
plt.xlabel('epoch')
plt.legend(['training set', 'validation set'], loc='upper right')
plt.show()




#examples for using generator to generate the training image on the fly
import os
import csv

samples = []
with open('./driving_log.csv') as csvfile:
    reader = csv.reader(csvfile)
    for line in reader:
        samples.append(line)

from sklearn.model_selection import train_test_split
train_samples, validation_samples = train_test_split(samples, test_size=0.2)

import cv2
import numpy as np
import sklearn

def generator(samples, batch_size=32):
    num_samples = len(samples)
    while 1: # Loop forever so the generator never terminates
        shuffle(samples)
        for offset in range(0, num_samples, batch_size):
            batch_samples = samples[offset:offset+batch_size]

            images = []
            angles = []
            for batch_sample in batch_samples:
                name = './IMG/'+batch_sample[0].split('/')[-1]
                center_image = cv2.imread(name)
                center_angle = float(batch_sample[3])
                images.append(center_image)
                angles.append(center_angle)

            # trim image to only see section with road
            X_train = np.array(images)
            y_train = np.array(angles)
            yield sklearn.utils.shuffle(X_train, y_train)

# compile and train the model using the generator function
train_generator = generator(train_samples, batch_size=32)
validation_generator = generator(validation_samples, batch_size=32)

ch, row, col = 3, 80, 320  # Trimmed image format

model = Sequential()
# Preprocess incoming data, centered around zero with small standard deviation
model.add(Lambda(lambda x: x/127.5 - 1.,
        input_shape=(ch, row, col),
        output_shape=(ch, row, col)))
model.add(... finish defining the rest of your model architecture here ...)

model.compile(loss='mse', optimizer='adam')
model.fit_generator(train_generator, samples_per_epoch= /
            len(train_samples), validation_data=validation_generator, /
            nb_val_samples=len(validation_samples), nb_epoch=3)

"""
If the above code throw exceptions, try
model.fit_generator(train_generator, steps_per_epoch= len(train_samples),
validation_data=validation_generator, validation_steps=len(validation_samples), epochs=5, verbose = 1)
"""

#aws EC2 GUP set up 
#to login aws and lauch the instance
https://ap-southeast-2.console.aws.amazon.com/ec2/v2/home?region=ap-southeast-2#Instances:sort=instanceId

#connect the instance through ssh
ssh -i "self_driving.pem" ubuntu@ec2-13-211-219-202.ap-southeast-2.compute.amazonaws.com
#copy the local file to the ec2 instance 
scp -r -i "self_driving.pem"  ./data  ubuntu@ec2-13-211-219-202.ap-southeast-2.compute.amazonaws.com:/home/ubuntu/Behavior_cloning_self_driving

#git lfs to push large file to github
https://github.com/git-lfs/git-lfs/wiki/Tutorial






#+++++++++++++++++++++++++++++++++++++++



#============================================================================
#Yolo
#remove the boxes with score less than the threshhold and select the box in the with the 
#score in the descending order and remove the surrounding boxes with the IOU greather than 0.5 
#repeat until there is no boxes whos score is less than the current box
#A 1-D integer Tensor of shape [M] representing the selected indices from the boxes tensor, where M <= max_output_size.
#http://machinethink.net/blog/object-detection/
#https://medium.com/@vivek.yadav/part-1-generating-anchor-boxes-for-yolo-like-network-for-vehicle-detection-using-kitti-dataset-b2fe033e5807
tf.image.non_max_suppression(
    boxes,
    scores,
    max_output_size,
    iou_threshold=0.5,
    score_threshold=float('-inf'),
    name=None
)

#Gather slices from params axis axis according to indices.
tf.gather(
    params,
    indices,
    validate_indices=None,
    name=None,
    axis=0
)

