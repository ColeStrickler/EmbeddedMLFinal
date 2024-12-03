import tensorflow_datasets as tfds
import tensorflow as tf
import scipy.io.wavfile as wavfile
import os
import shutil
# Load the Google Speech Commands dataset
dataset, info = tfds.load('speech_commands', with_info=True, as_supervised=True)
print(info)
# Access the training and testing sets
train_data, test_data = dataset['train'], dataset['test']
original_labels = info.features['label'].names

audio = info.features['audio']


def delete_all_folder(folder):
    for filename in os.listdir(folder):
        file_path = os.path.join(folder, filename)
        if os.path.isfile(file_path):  # Check if it's a file (and not a directory)
            os.remove(file_path)  # Delete the file
        else:
            shutil.rmtree(file_path)



# Save the dataset as TFRecord files
def save_to_tfrecord(dataset, filename):
    def _bytes_feature(value):
        """Returns a bytes_list from a string / byte."""
        return tf.train.Feature(bytes_list=tf.train.BytesList(value=[tf.io.encode_wav(value).numpy()]))

    def _int64_feature(value):
        """Returns an int64_list from a bool / enum / int / uint."""
        return tf.train.Feature(int64_list=tf.train.Int64List(value=value))

    # Create a TFRecord writer
    with tf.io.TFRecordWriter(filename) as writer:
        for audio, label in dataset:
            print(type(audio))
            audio_wav = tf.io.encode_wav(audio, sample_rate=16000)
            feature = {
                'audio': _bytes_feature(audio_wav.numpy()),
                'label': _int64_feature([label]),
            }
            example = tf.train.Example(features=tf.train.Features(feature=feature))
            writer.write(example.SerializeToString())




def map_labels(dataset, label_mapping):
    """
    Maps the original labels to new labels based on the label_mapping.
    """
    new_dataset = []

    for audio, label in dataset:
        # Get the original label name from the label index
        original_label_name = original_labels[label.numpy()]
        
        # Map the original label to the new label
        new_label_name = label_mapping.get(original_label_name, original_label_name)
        #print(new_label_name)
        # Get the new label index based on the modified label
        #new_label = original_labels.index(new_label_name)
        #print(new_label)
        # Append the (audio, new_label) tuple to the new dataset
        new_dataset.append((audio, new_label_name))
        #print(new_dataset)
    
    return new_dataset

# clear any old data
delete_all_folder("./data/")



# go = start driving
# up = speed up
# down = slow down
# left = shift path left
# right = shift path right
# stop = stop car
label_mapping = {
    'yes': 'other',
    'no': 'other',
    'up': 'up',
    'down': 'down',
    'left': 'left',
    'right': 'right',
    'on': 'other',
    'off': 'other',
    'stop': 'stop',
    'go': 'go',
    '_silence_': 'silence',
    '_unknown_': 'unknown'
}

for old_name, new_name in label_mapping.items():
        try:
            os.makedirs(f"./data/{new_name}")
        except FileExistsError as e:
            continue





train_data_mapped = map_labels(train_data, label_mapping)
test_data_mapped = map_labels(test_data, label_mapping)


# Save the modified train and test datasets
#save_to_tfrecord(train_data_mapped, 'train_data_mapped.tfrecord')
#save_to_tfrecord(test_data_mapped, 'test_data_mapped.tfrecord')

j = 0
for i, (audio, label) in enumerate(train_data_mapped):
    wavfile.write(f'data/{label}/{label}.{j}.wav', 16000, audio.numpy()) # Adjust sample rate as needed
    j += 1

for i, (audio, label) in enumerate(test_data_mapped):
    wavfile.write(f'data/{label}/{label}.{j}.wav', 16000, audio.numpy()) # Adjust sample rate as needed
    j += 1