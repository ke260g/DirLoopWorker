# Dir Loop Worker
+ A worker loops a dir recursively, written in Qt5.7
+ Retrieve the specific suffix files to another dir
+ Retain the directory structure of the files

# Screenshots
![Main Window](screenshots/mwin.png?raw=true "")

# Details
+ It is just a demo, which prints src-filenames and dst-filenames
+ You can add your actual working codes in `WorkerThread::loopDir`
+ You can build another `filesFilter` to specify another suffix files
+ Remember to create the new directory.

# Instance.01
### convert all images to gray
+ filesFilter
`QStringList() << "*.png *.jpeg *.jpg"`
+ working codes
```
cv::Mat img = cv::imread(inFilename.toStdString().c_str(), 0);
const static QDir mDir;
mDir.mkpath(prefix);
cv::imwrite(outFilename.toStdString().c_str(), img);
```

# Instance.02
### copy out all docx files
+ filesFilter
`QStringList() << "*.docx"`
+ working codes
```
const static QDir mDir;
mDir.mkpath(prefix);
QFile::copy(inFilename, outFilename);
```
