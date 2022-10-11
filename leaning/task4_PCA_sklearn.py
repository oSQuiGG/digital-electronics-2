import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
from sklearn.decomposition import PCA
from biplot import biplot


df = pd.read_csv('california_housing.csv')

features = df.iloc[:, :8].values
labels  = df.iloc[:, 8].values
feature_names = df.columns.values.tolist()

perm = np.random.permutation(features.shape[0])
perm_train = perm[:10000]
perm_test = perm[10000:]

features_train = features[perm_train , :]
features_test = features[perm_test, :]

labels_train = labels[perm_train ]
labels_test = labels[perm_test]

from sklearn.neighbors import KNeighborsRegressor

# standardization
mean = np.mean(features_train, axis = 0)
std = np.std(features_train, axis = 0)


### optimize k of kNN with grid search

features_train = (features_train - mean) / std
features_test = (features_test - mean) / std

mses = np.zeros(8)
pcas = []
knns = []
for n_com in range (1, 9):

    pca = PCA(n_components=n_com)


    pca.fit(features_train)
    pcas.append(pca)
   
    transformed_train = pca.transform(features_train)
    transformed_test = pca.transform(features_test)
    
    
    
    model = KNeighborsRegressor(3)
    model.fit(transformed_train, labels_train)
    knns.append(model)
    prediction = model.predict(transformed_test)
    
    mse = np.mean((prediction - labels_test)**2)
    mses[n_com - 1] = mse
    
    best_n = np.argmin(mses)

print(best_n)

plt.plot(mses)





# biplot(score,coeff,labels=labels,names=feature_names)














