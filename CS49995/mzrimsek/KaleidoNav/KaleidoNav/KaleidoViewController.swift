//
//  KaleidoViewController.swift
//  KaleidoTab
//
//  Created by Mike Zrimsek on 4/11/17.
//  Copyright © 2017 Mike Zrimsek. All rights reserved.
//

import UIKit

class KaleidoViewController: UIViewController {
    
    var isPaused = false
    var configViewContoller : ConfigViewController?
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        let storyBoard : UIStoryboard = UIStoryboard(name: "Main", bundle:nil)
        configViewContoller = storyBoard.instantiateViewController(withIdentifier: "ConfigViewController") as! ConfigViewController
        
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
        self.navigationController?.pushViewController(configViewContoller!, animated: true)
    }
    
}
