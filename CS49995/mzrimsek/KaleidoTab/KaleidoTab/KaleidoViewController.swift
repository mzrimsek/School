//
//  FirstViewController.swift
//  KaleidoTab
//
//  Created by Mike Zrimsek on 3/22/17.
//  Copyright © 2017 Mike Zrimsek. All rights reserved.
//

import UIKit

class KaleidoViewController: UIViewController {
    
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
