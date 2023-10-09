from PIL import Image
from ultralytics import YOLO

# Load a pretrained YOLOv8n model
model = YOLO('C:\\Users\\tbx12\\Desktop\\train45\\weights\\best.pt')

# Run inference on 'bus.jpg'
results = model('C:\\Users\\tbx12\\Desktop\\downloaded_image.jpg')  # results list

# Show the results
for r in results:
    im_array = r.plot()  # plot a BGR numpy array of predictions
    im = Image.fromarray(im_array[..., ::-1])  # RGB PIL image
    im.show()  # show image
    im.save('C:\\Users\\tbx12\\Desktop\\results.jpg')  # save imag