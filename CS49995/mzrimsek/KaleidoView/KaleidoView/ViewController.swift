//
//  ViewController.swift
//  KaleidoView
//
//  Created by Mike Zrimsek on 3/1/17.
//  Copyright © 2017 Mike Zrimsek. All rights reserved.
//

import UIKit

class ViewController: UIViewController {

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
}

