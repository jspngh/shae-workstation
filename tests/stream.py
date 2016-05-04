from subprocess import Popen

stream_server = Popen(['gst-launch-1.0', 'videotestsrc', '!', 'x264enc', '!',
               'queue', '!', 'rtph264pay', 'pt=96' ,'!' ,'udpsink', 'host=127.0.0.1', 'port=5000']);
