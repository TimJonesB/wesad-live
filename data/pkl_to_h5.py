import pickle
import h5py

sample_index = 2

fp = f'WESAD/S{sample_index}/S{sample_index}.pkl'
fout = f'S{sample_index}.h5'

with open(fp, 'rb') as f:
    data = pickle.load(f, encoding='latin1')

with h5py.File(fout, 'w') as f:
    f.create_dataset('label', data = data['label'])
    f.create_group('signal')
    f.attrs['source'] = fp
    for comp in ['chest', 'wrist']:
        print(comp)
        f['signal'].create_group(comp)
        for key in data['signal'][comp]:
            print(key)
            d = data['signal'][comp][key]
            f['signal'][comp].create_dataset(key, data=d, dtype=d.dtype)
