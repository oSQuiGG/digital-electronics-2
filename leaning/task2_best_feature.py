import numpy as np
import pandas as pd
import matplotlib.pyplot as plt



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





##### standardize the data 

#####


from sklearn.neighbors import KNeighborsRegressor

num_of_features = features_train.shape[1]

mses = np.zeros(49)


for n_neigh in range(1,50):
    
    model = KNeighborsRegressor(n_neigh)
    model.fit(features_train, labels_train)
    prediction = model.predict(features_test)
    
    mse = np.mean((prediction - labels_test)**2)
    mses[n_neigh - 1] = mse
    
best_neigh = np.argmin(mses)

print(best_neigh)

plt.plot(mses)


    

    
    
    
    







