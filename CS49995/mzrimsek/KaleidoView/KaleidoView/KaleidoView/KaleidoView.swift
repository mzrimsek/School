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
    
    var useAlpha = false
    
    var delay : TimeInterval = 0.5
    var timer : Timer?
    
    var views : [UIView] = Array()
    var currentView = 0
    var viewCount = 100
    
    func move() {
        if views.count < viewCount {
            addNewView()
            currentView = views.count - 1
        }
        
        let newFrame = getFrame()
        let backgroundColor = getRandomColor()
        views[currentView].frame = newFrame
        views[currentView].backgroundColor = backgroundColor
        currentView += 1
        if currentView >= views.count {
            currentView = 0
        }
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
    
    func addNewView() {
        let kaleidoSubview = UIView()
        views.append(kaleidoSubview)
        self.addSubview(kaleidoSubview)
    }
    
    func getFrame() -> (CGRect) {
        let randX = getRandomFrom(min:0.0, thruMax:frame.size.width/2)
        let randY = getRandomFrom(min:0.0, thruMax:frame.size.height/2)
        let randWidth = getRandomFrom(min: 20, thruMax: 60)
        let randHeight = getRandomFrom(min: 20, thruMax: 60)
        
        let newFrame = CGRect(x: randX, y: randY, width: randWidth, height: randHeight)
        
        
        return (ul:newFrame)
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
