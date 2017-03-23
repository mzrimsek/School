//
//  ConfigViewController.swift
//  KaleidoTab
//
//  Created by Mike Zrimsek on 3/22/17.
//  Copyright © 2017 Mike Zrimsek. All rights reserved.
//

import UIKit

class ConfigViewController: UIViewController {
    
    @IBOutlet var rectangleCountLabel: UILabel!
    @IBOutlet var speedLabel: UILabel!
    
    var kaleidoViewContoller : KaleidoViewController?
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        kaleidoViewContoller = tabBarController?.viewControllers?[0] as? KaleidoViewController
    }
    
    override var prefersStatusBarHidden: Bool {
        return true
    }
    
    @IBAction func updateRectangleCount(_ sender: UISlider) {
        let newCount = Int(sender.value)
        
        let kaleidoView = kaleidoViewContoller?.view as! KaleidoView
        
        rectangleCountLabel.text = "(" + String(newCount) + ")"
        //kaleidoView.viewCount = newCount
        //kaleidoView.removeSubviews()
    }
    @IBAction func updateSpeed(_ sender: UISlider) {
        let newDelay = TimeInterval(sender.value)
        
        let kaleidoView = kaleidoViewContoller?.view as! KaleidoView
        
        speedLabel.text = "(" + String(newDelay) + ")"
        kaleidoView.delay = newDelay
        kaleidoView.stopDrawing()
        kaleidoView.startDrawing()
    }
}

