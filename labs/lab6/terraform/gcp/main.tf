module "compute-instance" {
  source = "../../../../terraform/gcp"

  credentials = var.credentials
  project-id  = var.project-id

  name             = "pcpc-lab6"
  ssh-user         = "root"
  ssh-pk-save-path = var.ssh-pk-save-path
  machines-count   = var.count-vms
  cloud-init-file  = "cloud-init.yaml"
  # run "cloud-init status --wait" in the SSH to check when it is done
  # run "tail -f /var/log/cloud-init-output.log" to see what it is doing
}
