//
//  ConfigViewController.swift
//  KaleidoTab
//
//  Created by Mike Zrimsek on 4/11/17.
//  Copyright © 2017 Mike Zrimsek. All rights reserved.
//

import UIKit

class ConfigViewController: UIViewController {
    @IBOutlet var speedLabel: UILabel!
    @IBOutlet var rectangleCountLabel: UILabel!
    @IBOutlet var minDimensionLabel: UILabel!
    @IBOutlet var minDimensionStepper: UIStepper!
    @IBOutlet var maxDimensionLabel: UILabel!
    @IBOutlet var maxDimensionStepper: UIStepper!
    
    var kaleidoViewContoller : KaleidoViewController?
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        kaleidoViewContoller = navigationController?.viewControllers[0] as? KaleidoViewController
    }
    
    override var prefersStatusBarHidden: Bool {
        return true
    }
    
    @IBAction func updateSpeed(_ sender: UISlider) {
        let displayValue = (sender.value*100).rounded()/100
        let newDelay = TimeInterval(1-sender.value)
        
        let kaleidoView = kaleidoViewContoller?.view as! KaleidoView
        
        speedLabel.text = "(" + String(displayValue) + ")"
        kaleidoView.delay = newDelay
        if !(kaleidoViewContoller?.isPaused)! {
            kaleidoView.stopDrawing()
            kaleidoView.startDrawing()
        }
    }
    
    @IBAction func updateRectangleCount(_ sender: UISlider) {
        let newCount = Int(sender.value)*4
        
        let kaleidoView = kaleidoViewContoller?.view as! KaleidoView
        
        rectangleCountLabel.text = "(" + String(newCount) + ")"
        kaleidoView.viewCount = newCount
        kaleidoView.removeSubviews()
    }
    
    @IBAction func updateMinDimension(_ sender: UIStepper) {
        let newMin = CGFloat(sender.value)
        
        let kaleidoView = kaleidoViewContoller?.view as! KaleidoView
        
        minDimensionLabel.text = "(" + String(Int(newMin)) + ")"
        maxDimensionStepper.minimumValue = Double(newMin)
        kaleidoView.rectMinDimension = newMin
    }
    
    @IBAction func updateMaxDimension(_ sender: UIStepper) {
        let newMax = CGFloat(sender.value)
        
        let kaleidoView = kaleidoViewContoller?.view as! KaleidoView
        
        maxDimensionLabel.text = "(" + String(Int(newMax)) + ")"
        minDimensionStepper.maximumValue = Double(newMax)
        kaleidoView.rectMaxDimension = newMax
    }
}

