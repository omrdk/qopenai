#include <UIKit/UIKit.h>

#include <QtGui>
#include <QtQuick>

#include "ImagePicker.h"

@interface PhotosDelegate : NSObject <UIImagePickerControllerDelegate, UINavigationControllerDelegate> {
    ImagePicker *_imagePicker;
}
@end

@implementation PhotosDelegate

- (id) initWithIOSPhotos:(ImagePicker *)imagePicker {
    self = [super init];
    if (self) {
        _imagePicker = imagePicker;
    }
    return self;
}

- (void)imagePickerController:(UIImagePickerController *)picker didFinishPickingMediaWithInfo:(NSDictionary *)info {
    Q_UNUSED(picker);

    // Create the path where we want to save the image:
    NSString *path = [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) objectAtIndex:0];
    path = [path stringByAppendingString:@"/selected_image.png"];

    // Save image:
    UIImage *image = [info objectForKey:UIImagePickerControllerOriginalImage];
    [UIImagePNGRepresentation(image) writeToFile:path options:NSAtomicWrite error:nil];

    // Update selectedImage property to trigger QML code:
    _imagePicker->setSelectedImage(QString::fromNSString(path));

    // Bring back Qt's view controller:
    UIViewController *rvc = [[[UIApplication sharedApplication] keyWindow] rootViewController];
    [rvc dismissViewControllerAnimated:YES completion:nil];
}

@end

ImagePicker::ImagePicker(QQuickItem *parent) : QQuickItem(parent), m_delegate([[PhotosDelegate alloc] initWithIOSPhotos:this]) {
  ;
}

void ImagePicker::open()
{
    @try {
      QQuickWindow *window = this->window();
      window->show();

      // Get the UIView that backs our QQuickWindow:
      UIView* view = (__bridge UIView*)reinterpret_cast<void*>(window->winId());
      UIViewController *qtController = [[view window] rootViewController];

      // Create a new image picker controller to show on top of Qt's view controller:
      UIImagePickerController *imageController = [[[UIImagePickerController alloc] init] autorelease];
      [imageController setSourceType:UIImagePickerControllerSourceTypePhotoLibrary];
      [imageController setDelegate:id(m_delegate)];

      // Tell the imagecontroller to animate on top:
      [qtController presentViewController:imageController animated:YES completion:nil];
    }
    @catch (NSException* exception) {
        // Handle the exception here
        qDebug() << "Exception:" << QString::fromNSString(exception.description);
    }
}
