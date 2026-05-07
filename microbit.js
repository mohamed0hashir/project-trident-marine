enum RadioMessage {
 dew = 10533,
 message1 = 49434
}
input.onGesture(Gesture.EightG, function () {
 radio.sendString("Trident is crashed")
 radio.sendString("" + (input.rotation(Rotation.Pitch)))
 radio.sendString("" + (input.rotation(Rotation.Roll)))
})
input.onButtonPressed(Button.A, function () {
 record.playAudio(record.BlockingState.Blocking)
})
input.onGesture(Gesture.SixG, function () {
 radio.sendString("Trident is crashed")
 radio.sendString("" + (input.rotation(Rotation.Pitch)))
 radio.sendString("" + (input.rotation(Rotation.Roll)))
})
input.onSound(DetectedSound.Loud, function () {
 record.setMicGain(record.AudioLevels.High)
 record.startRecording(record.BlockingState.Nonblocking)
})
input.onGesture(Gesture.Shake, function () {
 radio.sendString("Trident is crashed")
 radio.sendString("" + (input.rotation(Rotation.Pitch)))
 radio.sendString("" + (input.rotation(Rotation.Roll)))
})
input.onGesture(Gesture.ThreeG, function () {
 radio.sendString("Trident is crashed")
 radio.sendString("" + (input.rotation(Rotation.Pitch)))
 radio.sendString("" + (input.rotation(Rotation.Roll)))
})
radio.setGroup(77)
basic.forever(function () {
 datalogger.log(
 datalogger.createCV("Pitch", input.rotation(Rotation.Pitch)),
 datalogger.createCV("Roll", input.rotation(Rotation.Roll))
 )
 datalogger.log(datalogger.createCV("Compass heading",
input.compassHeading()))
 datalogger.log(datalogger.createCV("Sound level",
input.soundLevel()))
 datalogger.log(datalogger.createCV("Acceleration",
input.acceleration(Dimension.Strength)))
 datalogger.log(datalogger.createCV("magnetic force", 0))
 if (input.magneticForce(Dimension.Strength) >= 0) {
 datalogger.log(datalogger.createCV("Magnetic presence", 1))
 } else {
 datalogger.log(datalogger.createCV("Magnetic presence", 0))
 }
 basic.pause(2000)
})
