//
//  KaleidoViewController.swift
//  KaleidoTab
//
//  Created by Mike Zrimsek on 3/22/17.
//  Copyright © 2017 Mike Zrimsek. All rights reserved.
//

import UIKit

class KaleidoViewController: UIViewController {
    
    var isPaused = false
    
    override func viewDidLoad() {
        super.viewDidLoad()
        let view = self.view as! KaleidoView
        view.startDrawing()
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
    }
    
    override var prefersStatusBarHidden: Bool {
        return true
    }
    
    @IBAction func handleTouch(_ sender: UITapGestureRecognizer) {
        let view = self.view as! KaleidoView
        if(isPaused) {
            view.startDrawing()
            isPaused = false
        }
        else {
            view.stopDrawing()
            isPaused = true
        }
    }
    
    @IBAction func handleDoubleTouch(_ sender: UITapGestureRecognizer) {
        let configController = ConfigViewController()
        self.navigationController?.pushViewController(configController, animated: true)
    }
}
