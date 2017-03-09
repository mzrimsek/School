//
//  KaleidoView.swift
//  KaleidoView
//
//  Created by Mike Zrimsek on 3/1/17.
//  Copyright © 2017 Mike Zrimsek. All rights reserved.
//

import UIKit

class KaleidoView : UIView {
    
    var colorMin : CGFloat = 0.0
    var colorMax : CGFloat = 1.0
    var alphaMin : CGFloat = 0.0
    var alphaMax : CGFloat = 1.0
    
    var rectMinDimension : CGFloat = 20
    var rectMaxDimension : CGFloat = 150
    
    var useAlpha = false
    
    var delay : TimeInterval = 0.25
    var timer : Timer?
    
    var views : [UIView] = Array()
    var currentView = 0
    var viewCount = 200
    
    func move() {
        if views.count < viewCount {
            addNewViews()
            currentView = views.count - 4
        }
        
        let newFrames = getFrame()
        let backgroundColor = getRandomColor()
        
        drawFrame(frame: newFrames.topLeft, color: backgroundColor)
        drawFrame(frame: newFrames.topRight, color: backgroundColor)
        drawFrame(frame: newFrames.bottomLeft, color: backgroundColor)
        drawFrame(frame: newFrames.bottomRight, color: backgroundColor)
        
        if currentView >= views.count {
            currentView = 0
        }
    }
    
    func drawFrame(frame: CGRect, color: UIColor) {
        views[currentView].frame = frame
        views[currentView].backgroundColor = color
        currentView += 1
    }
    
    func startDrawing()
    {
        timer = Timer(timeInterval: delay,
                      target      : self,
                      selector    : #selector(KaleidoView.move),
                      userInfo    : nil,
                      repeats     : true)
        
        let runLoop = RunLoop.current
        runLoop.add(timer!, forMode:RunLoopMode(rawValue:"NSDefaultRunLoopMode"))
    }
    
    func addNewViews() {
        for _ in 0...4 {
            let kaleidoSubview = UIView()
            views.append(kaleidoSubview)
            self.addSubview(kaleidoSubview)
        }
    }
    
    func getFrame() -> (topLeft: CGRect, topRight: CGRect, bottomLeft: CGRect, bottomRight: CGRect) {
        let rectAttrs = getRectAttributes()
        
        let topLeft = CGRect(x: rectAttrs.leftX, y: rectAttrs.topY, width: rectAttrs.width, height: rectAttrs.height)
        let topRight = CGRect(x: rectAttrs.rightX, y: rectAttrs.topY, width: rectAttrs.width, height: rectAttrs.height)
        let bottomLeft = CGRect(x: rectAttrs.leftX, y: rectAttrs.bottomY, width: rectAttrs.width, height: rectAttrs.height)
        let bottomRight = CGRect(x: rectAttrs.rightX, y: rectAttrs.bottomY, width: rectAttrs.width, height: rectAttrs.height)
        
        return (topLeft, topRight, bottomLeft, bottomRight)
    }
    
    func getRectAttributes() -> (leftX: CGFloat, rightX: CGFloat, topY: CGFloat, bottomY: CGFloat, width: CGFloat, height: CGFloat) {
        let centerX = frame.size.width/2
        let centerY = frame.size.height/2
        
        let leftX = getRandomFrom(min:0.0, thruMax:centerX)
        let topY = getRandomFrom(min:0.0, thruMax:centerY)
        
        let rectWidth = getRandomFrom(min: rectMinDimension, thruMax: rectMaxDimension)
        let rectHeight = getRandomFrom(min: rectMinDimension, thruMax: rectMaxDimension)
        
        let rightX = 2*centerX - leftX - rectWidth
        let bottomY = 2*centerY - topY - rectHeight
        
        return (leftX: leftX, rightX: rightX, topY: topY, bottomY: bottomY, width: rectWidth, height: rectHeight)
    }
    
    func getRandomColor() -> UIColor
    {
        let randRed   = getRandomFrom(min:colorMin, thruMax:colorMax)
        let randGreen = getRandomFrom(min:colorMin, thruMax:colorMax)
        let randBlue  = getRandomFrom(min:colorMin, thruMax:colorMax)
        
        var alpha : CGFloat = 1.0
        if useAlpha{
            alpha = getRandomFrom(min:alphaMin, thruMax:alphaMax)
        }
        
        return UIColor(red:randRed, green:randGreen, blue:randBlue, alpha:alpha)
    }
    
    func getRandomFrom(min:CGFloat, thruMax max:CGFloat)-> CGFloat
    {
        guard max > min else {
            return min
        }
        
        let randomNum = Int(arc4random() / 2)
        
        let accuracy : CGFloat = 1000.0
        
        let scaledMin : CGFloat = min * accuracy
        let scaledMax : CGFloat = max * accuracy
        
        let randomInRange = CGFloat(randomNum % Int(scaledMax - scaledMin))
        let randomResult = randomInRange / accuracy + min
        
        return randomResult
    }
    
}
